import sys

inp = [line.rstrip() for line in sys.stdin.readlines()]

mitems = []
mops = []
mtests = []
inspect_cnt = []


def do_op(item, m):
    if mops[m]['op'] == '+':
        if mops[m]['n2'] == 'old':
            return item + item
        else:
            return item + int(mops[m]['n2'])
    elif mops[m]['op'] == '*':
        if mops[m]['n2'] == 'old':
            return item * item
        else:
            return item * int(mops[m]['n2'])
    raise Exception('fuck')


def inspect(m):
    inspect_cnt[m] += 1

    item = mitems[m][0]
    mitems[m].pop(0)

    item = do_op(item, m)
    # item = item // 3
    item = item % 9699690
    if item % mtests[m]['div'] == 0:
        mitems[mtests[m]['t']].append(item)
    else:
        mitems[mtests[m]['f']].append(item)


i = 0
for i in range(0, len(inp), 7): 
    s1 = inp[i+1]
    t = s1.removeprefix('  Starting items: ')
    items = list(map(int, t.split(', ')))
    mitems.append(items)

    s2 = inp[i+2]
    t = s2.removeprefix('  Operation: new = ').split(' ')
    op = {'op': t[1], 'n2': t[2]}
    mops.append(op)

    s3 = inp[i+3].removeprefix('  Test: divisible by ')
    s4 = inp[i+4].removeprefix('    If true: throw to monkey ')
    s5 = inp[i+5].removeprefix('    If false: throw to monkey ')
    test = {'div': int(s3), 't': int(s4), 'f': int(s5)}
    mtests.append(test)

    inspect_cnt.append(0)


for rnd in range(10000):
    for m in range(len(mitems)):
        while len(mitems[m]) > 0:
            inspect(m)

print(inspect_cnt)
inspect_cnt.sort(reverse=True)
print(inspect_cnt[0] * inspect_cnt[1])
