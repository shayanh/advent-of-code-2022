import os
import sys

pwd = []
fs = {}

def proc_cmd(line):
    global pwd
    global fs

    parts = line.split()
    cmd = parts[1]
    if cmd == 'cd':
        arg = parts[2]
        if arg == '/':
            pwd = ['/']
        elif arg == '..':
            pwd.pop()
        else:
            pwd.append(arg)


def get_abs_path(pwd):
    return os.path.join(*pwd)


def proc_output(line):
    abs_path = get_abs_path(pwd)
    if abs_path not in fs:
        fs[abs_path] = []

    parts = line.split(' ')
    if parts[0] == 'dir':
        fs[abs_path].append({'typ': 'd', 'name': parts[1]})
    else:
        fs[abs_path].append({'typ': 'f', 'name': parts[1], 'size': int(parts[0])})


total_size = {}


def get_total_size(path):
    if path in total_size:
        return total_size[path]

    res = 0
    for c in fs[path]:
        if c['typ'] == 'd':
            res += get_total_size(os.path.join(path, c['name']))
        else:
            res += c['size']
    total_size[path] = res
    return res


def main():
    inp = sys.stdin.readlines()

    for line in inp:
        line = line.rstrip()

        if line.startswith('$'):
            proc_cmd(line)
        else:
            proc_output(line)

    unused = 70000000 - get_total_size('/')
    freeup = 30000000 - unused

    ans = 1e15
    for path in fs:
        t = get_total_size(path)
        if t >= freeup:
            ans = min(ans, t)
    print(ans)


if __name__ == '__main__':
    main()
