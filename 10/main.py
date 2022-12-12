import sys

inp = [line.rstrip() for line in sys.stdin.readlines()]

cycle = 0
x = 1
ans = 0

check_cycles = list(range(20, 240, 40))

crt = []

def inc_cycle():
    global cycle
    global x
    global ans

    cycle += 1
    pos = (cycle - 1) % 40
    if pos-1 <= x <= pos+1:
        crt.append('#')
    else:
        crt.append('.')
    # for check in check_cycles:
        # if cycle == check:
            # ans += cycle * x


for cmd in inp:
    parts = cmd.split(' ')
    if parts[0] == 'noop':
        inc_cycle()
    else:
        inc_cycle()
        inc_cycle()
        x += int(parts[1])

# print(check_cycles)
# print(ans)
for i in range(6):
    for j in range(40):
        print(crt[i*40 + j], end='')
    print()
