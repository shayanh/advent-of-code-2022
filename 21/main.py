import sys

inp = [line.rstrip() for line in sys.stdin.readlines()]

v = {}

for line in inp:
    l, r = line.split(": ")
    if r.isdigit():
        v[l] = {'type': 'num', 'val': int(r)}
    else:
        v[l] = {
            'type': 'op',
            'op': r[5],
            'l': r[0:4],
            'r': r[7:]
        }

def solve(x):
    if v[x]['type'] == 'num':
        return v[x]['val']

    o = v[x]['op']
    if o == '+':
        return solve(v[x]['l']) + solve(v[x]['r'])
    if o == '-':
        return solve(v[x]['l']) - solve(v[x]['r'])
    if o == '/':
        return solve(v[x]['l']) // solve(v[x]['r'])
    if o == '*':
        return solve(v[x]['l']) * solve(v[x]['r'])
    return 1

# print(solve('root'))

l = 0
r = 10**20
while r - l > 1:
    m = (l + r) // 2
    v['humn'] = {'type': 'num', 'val': m}

    # print(l, r, m)

    t1 = solve('vtsj')
    t2 = solve('tfjf')
    if t1 > t2:
        l = m
    else:
        r = m

print(r)

v['humn'] = {'type': 'num', 'val': r}
t1 = solve('vtsj')
t2 = solve('tfjf')
print(t1, t2)
assert t1 == t2
