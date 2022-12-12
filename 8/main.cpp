#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> a;

void part1() {
    int n = a.size(), m = a[0].size();

    auto checkCol = [n](int x, int y) {
        bool check = true;
        for (int i = 0; i < x; i++) {
            if (a[i][y] >= a[x][y]) {
                check = false;
            }
        }
        if (check) {
            return true;
        }

        check = true;
        for (int i = x+1; i < n; i++) {
            if (a[i][y] >= a[x][y]) {
                check = false;
            }
        }
        return check;
    };

    auto checkRow = [m](int x, int y) {
        bool check = true;
        for (int j = 0; j < y; j++) {
            if (a[x][j] >= a[x][y]) {
                check = false;
            }
        }
        if (check) {
            return true;
        }

        check = true;
        for (int j = y+1; j < m; j++) {
            if (a[x][j] >= a[x][y]) {
                check = false;
            }
        }
        return check;
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (checkCol(i, j) || checkRow(i, j)) {
                ans++;
            }
        }
    }
    cout << ans << endl;
}

void part2() {
    int n = a.size(), m = a[0].size();

    auto in_range = [n, m](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };
    auto go = [in_range](int x, int y, int dx, int dy) {
        int res = 0;

        int cx = x + dx;
        int cy = y + dy;
        while (in_range(cx, cy)) {
            res++;
            if (a[cx][cy] >= a[x][y]) {
                break;
            }
            cx += dx; cy += dy;
        }

        return res;
    };

    int ans = 0;
    int dx[] = {+1, -1, 0, 0};
    int dy[] = {0, 0, +1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cnt = 1;
            for (int k = 0; k < 4; k++) {
                cnt *= go(i, j, dx[k], dy[k]);
            }

            ans = max(ans, cnt);
        }
    }

    cout << ans << endl;
}

int main() {
    string s;
    while (cin >> s) {
        a.push_back(s);
    }

    //part1();
    part2();

    return 0;
}
