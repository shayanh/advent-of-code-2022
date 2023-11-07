import sys


class Board:
    def __init__(self, char_board: list[str]):
        self.data = char_board
        self.n = len(char_board)
        self.m = max([len(r) for r in char_board])

    def __getitem__(self, item):
        return self.data[item]


class Agent:
    def __init__(self, board: Board):
        self.board = board
        self.x = 0
        for i, c in enumerate(board[self.x]):
            if c == '.':
                self.y = i
                break
        self.dir = 0  # right

    def _move_step(self):
        def get_delta():
            match self.dir:
                case 0:
                    return 0, 1
                case 1:
                    return 1, 0
                case 2:
                    return 0, -1
                case 3:
                    return -1, 0
                case _:
                    raise ValueError

        def in_range(x, y):
            return 0 <= x < self.board.n and 0 <= y < len(self.board[x])

        dx, dy = get_delta()

        def rec(x: int, y: int) -> (int, int):
            cx, cy = x + dx, y + dy
            if cx >= self.board.n and dx == 1:
                return rec(-1, cy)
            if cx < 0 and dx == -1:
                return rec(self.board.n, cy)
            if cy >= self.board.m and dy == 1:
                return rec(cx, -1)
            if cy < 0 and dy == -1:
                return rec(cx, self.board.m)
            if not in_range(cx, cy):
                return rec(cx, cy)
            match self.board[cx][cy]:
                case ' ':
                    return rec(cx, cy)
                case '.':
                    return cx, cy
                case '#':
                    return self.x, self.y
                case _:
                    raise ValueError

        self.x, self.y = rec(self.x, self.y)

    def _move_forward(self, n: int):
        for _ in range(n):
            self._move_step()

    def move(self, cmd: str | int):
        match cmd:
            case 'R':
                self.dir = (self.dir + 1) % 4
            case 'L':
                self.dir = (self.dir - 1) % 4
            case int(n):
                self._move_forward(n)
            case _:
                raise ValueError


def solve(cmd: str, char_board: list[str]):
    board = Board(char_board)
    agent = Agent(board)
    curr = 0
    for c in cmd:
        if c.isdigit():
            curr = curr * 10 + int(c)
        else:
            if curr > 0:
                agent.move(curr)
                curr = 0
            agent.move(c)
    if curr > 0:
        agent.move(curr)

    ans = 1000 * (agent.x + 1) + 4 * (agent.y + 1) + agent.dir
    return ans


def main():
    inp = [line[:-1] for line in sys.stdin.readlines()]
    board = inp[:-2]
    cmd = inp[-1]
    print(solve(cmd, board))


main()
