import sys
import functools

inp = [line.rstrip() for line in sys.stdin.readlines()]

"""
-1: p1 < p2
 0: p1 == p2
+1: p1 > p2
"""
def cmp(p1, p2):
    match p1, p2:
        case list(l1), list(l2):
            if len(l1) == 0:
                if len(l2) == 0:
                    return 0
                return -1
            for i in range(len(l1)):
                if i >= len(l2):
                    return +1
                c = cmp(l1[i], l2[i])
                if c != 0:
                    return c
            assert len(l1) <= len(l2)
            if len(l2) > len(l1):
                return -1
            return 0
        case int(i1), int(i2):
            if i1 < i2:
                return -1
            elif i1 == i2:
                return 0
            else:
                return +1
        case list(l1), int(i2):
            return cmp(l1, [i2])
        case int(i1), list(l2):
            return cmp([i1], l2) 
    raise Exception('fuck')


def part1():
    j = 0
    ans = 0
    for i in range(0, len(inp), 3):
        p1 = eval(inp[i])
        p2 = eval(inp[i+1])
        if cmp(p1, p2) == -1:
            ans += j+1
        j += 1
    print(ans)


def part2():
    packets = []
    for line in inp:
        if line != '':
            packets.append(eval(line))
    packets.append([[2]])
    packets.append([[6]])
    packets.sort(key=functools.cmp_to_key(cmp))

    i1 = packets.index([[2]])+1
    i2 = packets.index([[6]])+1
    print(i1, i2)
    print(i1 * i2)


part1()
part2()
