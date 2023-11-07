package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"log/slog"
	"os"
	"strconv"
	"strings"
)

type Valve struct {
	Name string
	Rate int
	Adj  []string
}

var nameToValve map[string]*Valve
var valves []*Valve

func parseLine(line string) {
	words := strings.Split(line, " ")
	name := words[1]

	t := words[4]
	t = t[5 : len(t)-1]
	rate, _ := strconv.Atoi(t)

	var adj []string
	for i := 9; i < len(words); i++ {
		t := words[i]
		t = strings.TrimSuffix(t, ",")
		adj = append(adj, t)
	}

	valve := &Valve{
		Name: name,
		Rate: rate,
		Adj:  adj,
	}
	valves = append(valves, valve)
	nameToValve[name] = valve
}

var distances map[*Valve]map[*Valve]int

const INF = 1e9

func calcDistances() {
	distances = make(map[*Valve]map[*Valve]int)

	for _, v1 := range valves {
		distances[v1] = make(map[*Valve]int)
		for _, v2 := range valves {
			distances[v1][v2] = INF
		}
	}
	for _, v1 := range valves {
		distances[v1][v1] = 0
		for _, v2Name := range v1.Adj {
			distances[v1][nameToValve[v2Name]] = 1
		}
	}

	for _, k := range valves {
		for _, i := range valves {
			for _, j := range valves {
				distances[i][j] = min(distances[i][j], distances[i][k]+distances[k][j])
			}
		}
	}
}

type State struct {
	curr     *Valve
	mask     int
	t        int
	pressure int
}

func (s State) maskPressure() int {
	res := 0
	for i, v := range nonZero {
		if s.mask&(1<<i) != 0 {
			res += v.Rate
		}
	}
	return res
}

var cache map[int]int
var nonZero []*Valve

const T = 26

func f(start State) int {
	pq := &PriorityQueue{}
	heap.Init(pq)
	heap.Push(pq, start)

	res := 0
	for pq.Len() > 0 {
		s := heap.Pop(pq).(State)
		p := s.maskPressure()

		cache[s.mask] = max(cache[s.mask], s.pressure)
		res = max(res, s.pressure)

		if s.t == T {
			continue
		}

		newS := State{
			curr:     s.curr,
			mask:     s.mask,
			t:        T,
			pressure: s.pressure + p*(T-s.t),
		}
		heap.Push(pq, newS)

		for i, v := range nonZero {
			if s.mask&(1<<i) != 0 {
				continue
			}

			newT := s.t + distances[s.curr][v] + 1
			if newT > T {
				continue
			}
			addedP := (distances[s.curr][v]+1)*p + v.Rate
			newP := s.pressure + addedP
			newS := State{
				curr:     v,
				mask:     s.mask ^ (1 << i),
				t:        newT,
				pressure: newP,
			}
			heap.Push(pq, newS)
		}
	}
	return res
}

func Solve() int {
	cache = make(map[int]int)

	for _, v := range valves {
		if v.Rate > 0 {
			nonZero = append(nonZero, v)
		}
	}

	s := State{
		curr:     nameToValve["AA"],
		mask:     0,
		t:        1,
		pressure: 0,
	}
	return f(s)
}

func part2() int {
	res := 0
	for k1, v1 := range cache {
		for k2, v2 := range cache {
			if k1&k2 == 0 {
				res = max(res, v1+v2)
			}
		}
	}
	return res
}

func main() {
	logger := slog.New(slog.NewTextHandler(os.Stderr, &slog.HandlerOptions{
		Level: slog.LevelDebug,
	}))
	slog.SetDefault(logger)

	nameToValve = make(map[string]*Valve)
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		line := scanner.Text()
		parseLine(line)
	}

	calcDistances()
	fmt.Println(Solve())
	fmt.Println(part2())
}
