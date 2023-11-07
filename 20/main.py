import copy
import sys


def mix(seq: list[tuple[int, int]]) -> list[tuple[int, int]]:
    n = len(seq)
    res = copy.copy(seq)
    for i, _  in enumerate(seq):
        pos, e = next((j, k[1]) for j, k in enumerate(res) if k[0] == i)
        t = abs(e) % (n-1)
        for _ in range(t):
            nxt = (pos + (e // abs(e))) % n
            res[pos], res[nxt] = res[nxt], res[pos]
            pos = nxt
    return res


def part1(lines):
    seq = list(enumerate(map(int, lines)))
    t = mix(seq)
    p = next(i for i, v in enumerate(t) if v[1] == 0)
    n = len(t)
    return sum([t[(p + x) % n][1] for x in range(0, 3001, 1000)])


def part2(lines):
    seq = list(enumerate(map(int, lines)))
    decrypt_key = 811589153
    seq = list(map(lambda x: (x[0], x[1] * decrypt_key), seq))
    t = seq
    for _ in range(10): 
        t = mix(t)
    p = next(i for i, v in enumerate(t) if v[1] == 0)
    n = len(t)
    return sum([t[(p + x) % n][1] for x in range(0, 3001, 1000)])


inp = sys.stdin.readlines()

print(part1(inp))
print(part2(inp))
