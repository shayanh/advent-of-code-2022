import sys

inp = sys.stdin.readlines()

ans = 0

for line in inp:
    line = line.rstrip()
    parts = line.split(',')
    x1, y1 = map(int, parts[0].split('-'))
    x2, y2 = map(int, parts[1].split('-'))

    def contains(x1, y1, x2, y2):
        return x1 <= x2 and y1 >= y2

    if contains(x1, y1, x2, y2) or contains(x2, y2, x1, y1):
        ans += 1

print(ans)
