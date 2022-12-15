import sys


MAX_X = 1000
MAX_Y = 1000

a = [['.' for _ in range(MAX_Y)] for _ in range(MAX_X)]
max_x = 0

def proc_line(line):
    global max_x

    parts = line.split(' -> ')
    points = []
    for part in parts:
        y, x = map(int, part.split(','))
        points.append((x, y))
        max_x = max(max_x, x)

    for i in range(1, len(points)):
        x0, y0 = points[i-1]
        x1, y1 = points[i]

        if x0 == x1:
            for y in range(min(y0, y1), max(y0, y1)+1):
                a[x0][y] = '#'
        elif y0 == y1:
            for x in range(min(x0, x1), max(x0, x1)+1):
                a[x][y0] = '#'


def produce_sand():
    x, y = 0, 500
    while x < MAX_X-1:
        # print(x, y)

        if a[x+1][y] == '.':
            x += 1
        elif a[x+1][y-1] == '.':
            x += 1
            y -= 1
        elif a[x+1][y+1] == '.':
            x += 1
            y += 1
        else:
            assert a[x][y] == '.'
            a[x][y] = 'o'
            return x, y
            # return True
    # return False
    raise Exception('fuck')


def main():
    inp = [line.rstrip() for line in sys.stdin.readlines()]

    for line in inp:
        proc_line(line)
    
    for i in range(MAX_Y):
        a[max_x+2][i] = '#'

    ans = 0
    while True:
        x, y = produce_sand()
        if x == 0 and y == 500:
            break
        else:
            ans += 1
    print(ans+1)


main()
