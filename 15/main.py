import sys

inp = [line.rstrip() for line in sys.stdin.readlines()]

def part1():
    beacon = {}
    no_beacon = {}

    for line in inp:
        parts = line.split(' ')
        sx = int(parts[2].removeprefix('x=').removesuffix(','))
        sy = int(parts[3].removeprefix('y=').removesuffix(':'))
        
        bx = int(parts[8].removeprefix('x=').removesuffix(','))
        by = int(parts[9].removeprefix('y='))

        beacon[(bx, by)] = True

        d = abs(sx - bx) + abs(sy - by)

        j = 2000000
        for i in range(sx-d, sx+d+1):
            cd = abs(sx - i) + abs(sy - j)
            if cd <= d:
                no_beacon[(i, j)] = True

    ans = 0
    for x, y in no_beacon:
        if y == 2000000 and (x, y) not in beacon:
            ans += 1

    print(ans)


def part2():
    # MAX = 21
    MAX = 4000000+1
    segs = [[] for _ in range(MAX)]

    for line in inp:
        parts = line.split(' ')
        sx = int(parts[2].removeprefix('x=').removesuffix(','))
        sy = int(parts[3].removeprefix('y=').removesuffix(':'))
        
        bx = int(parts[8].removeprefix('x=').removesuffix(','))
        by = int(parts[9].removeprefix('y='))

        d = abs(sx - bx) + abs(sy - by)

        for i in range(max(0, sx-d), min(MAX, sx+d+1)):
            r = d - abs(sx - i)
            y1, y2 = sy-r, sy+r+1
            segs[i].append((y1, y2))

    def tuning_freq(x, y):
        return x * 4000000 + y

    for i in range(MAX):
        segs[i].sort()
        assert len(segs[i]) > 0

        curr_y1, curr_y2 = segs[i][0]
        for y1, y2 in segs[i]:
            if curr_y2 >= y2:
                continue
            if y1 > curr_y2:
                print(i, curr_y2, tuning_freq(i, curr_y2))
            curr_y1, curr_y2 = y1, y2


part2()
