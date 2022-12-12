def check(t):
    mark = {}
    for c in t:
        if c in mark:
            return False
        mark[c] = True
    return True

s = input()

for i in range(len(s)):
    if check(s[i:i+14]):
        print(i+14)
        break
