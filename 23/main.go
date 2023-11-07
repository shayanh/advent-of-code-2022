package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
)

type Elf struct {
	x, y int
}

func makeElf(x, y int) Elf {
	return Elf{x: x, y: y}
}

var moveDirs []string

func doStep(elves []Elf) []Elf {
	mark := make(map[Elf]bool)
	for _, elf := range elves {
		mark[elf] = true
	}

	getPos := func(elf Elf, dir string) (int, int) {
		switch dir {
		case "N":
			return elf.x - 1, elf.y
		case "NE":
			return elf.x - 1, elf.y + 1
		case "NW":
			return elf.x - 1, elf.y - 1
		case "S":
			return elf.x + 1, elf.y
		case "SE":
			return elf.x + 1, elf.y + 1
		case "SW":
			return elf.x + 1, elf.y - 1
		case "E":
			return elf.x, elf.y + 1
		case "W":
			return elf.x, elf.y - 1
		default:
			panic("")
		}
	}

	noElf := func(elf Elf, dirs ...string) bool {
		for _, dir := range dirs {
			if mark[makeElf(getPos(elf, dir))] {
				return false
			}
		}
		return true
	}

	canMove := func(elf Elf, dir string) bool {
		switch dir {
		case "N":
			return noElf(elf, "N", "NE", "NW")
		case "S":
			return noElf(elf, "S", "SE", "SW")
		case "W":
			return noElf(elf, "W", "NW", "SW")
		case "E":
			return noElf(elf, "E", "NE", "SE")
		}
		panic("")
	}

	proposeMove := func(elf Elf) Elf {
		if noElf(elf, "N", "NE", "NW", "S", "SE", "SW", "E", "W") {
			return elf
		}
		for _, dir := range moveDirs {
			if canMove(elf, dir) {
				return makeElf(getPos(elf, dir))
			}
		}
		return elf
	}

	var proposedMoves []Elf
	for _, elf := range elves {
		proposedMoves = append(proposedMoves, proposeMove(elf))
	}

	var res []Elf
	for i := range proposedMoves {
		found := false
		for j := range proposedMoves {
			if i != j && proposedMoves[i] == proposedMoves[j] {
				found = true
				break
			}
		}
		if found {
			res = append(res, elves[i])
		} else {
			res = append(res, proposedMoves[i])
		}
	}

	t := moveDirs[0]
	moveDirs = moveDirs[1:]
	moveDirs = append(moveDirs, t)

	return res
}

func solve(board []string) {
	var elves []Elf
	for i := range board {
		for j := range board[i] {
			if board[i][j] == '#' {
				elves = append(elves, Elf{x: i, y: j})
			}
		}
	}

	moveDirs = []string{"N", "S", "W", "E"}
	part1 := func(steps int) int {
		for i := 0; i < steps; i++ {
			elves = doStep(elves)
		}

		n := len(board)
		m := len(board[0])
		minX, minY := n, m
		maxX, maxY := 0, 0
		for _, elf := range elves {
			minX = min(minX, elf.x)
			minY = min(minY, elf.y)
			maxX = max(maxX, elf.x)
			maxY = max(maxY, elf.y)
		}

		return (maxX-minX+1)*(maxY-minY+1) - len(elves)
	}
	_ = part1

	part2 := func() int {
		for i := 0; ; i++ {
			newElves := doStep(elves)
			if slices.Equal(elves, newElves) {
				return i
			}
			elves = newElves
		}
	}
	fmt.Println(part2())
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	var board []string
	for scanner.Scan() {
		line := scanner.Text()
		board = append(board, line)
	}

	solve(board)
}
