import sys

inp = [line.rstrip() for line in sys.stdin.readlines()]

mark = {}
points = []

for line in inp:
    x, y, z = map(int, line.split(','))
    points.append((x, y, z))
    mark[(x, y, z)] = True

ans = 0

for x, y, z in points:
    def check(x, y, z):
        global ans
        if (x, y, z) not in mark:
            ans += 1
    check(x, y, z+1)
    check(x, y, z-1)
    check(x+1, y, z)
    check(x-1, y, z)
    check(x, y+1, z)
    check(x, y-1, z)

print(ans)
