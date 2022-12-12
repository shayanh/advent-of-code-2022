#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define VAL(x) #x << " = " << x << "   "

int main() {
    vector<string> a;

    string s;
    while (cin >> s) {
        a.push_back(s);
    }

    int n = a.size(), m = a[0].size();
    pair<int, int> st, en;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'S') {
                a[i][j] = 'a';
                st = {i, j};
            } else if (a[i][j] == 'E') {
                a[i][j] = 'z';
                en = {i, j};
            }
        }
    }

    const int INF = 1e9;

    auto bfs = [&a, &n, &m, &INF](pair<int, int> s, pair<int, int> e) {
        queue<pair<int, int> > q;

        vector<vector<int>> dis(n, vector<int>(m, INF));

        q.push(s);
        dis[s.first][s.second] = 0;

        int dx[] = {+1, -1, 0, 0};
        int dy[] = {0, 0, +1, -1};

        auto in_range = [&n, &m](int x, int y) {
            return x >= 0 && x < n && y >= 0 && y < m;
        };

        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            int d = dis[x][y];

            for (int i = 0; i < 4; i++) {
                int cx = x + dx[i], cy = y + dy[i];
                if (!in_range(cx, cy)) {
                    continue;
                }

                int elevd = a[cx][cy] - a[x][y];
                if (elevd <= 1 && dis[cx][cy] > d+1) {
                    q.push({cx, cy});
                    dis[cx][cy] = d+1;
                }
            }
        }

        return dis[e.first][e.second];
    };

    //cout << bfs(st, en) << endl;
    
    int ans = INF;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] != 'a') {
                continue;
            }

            int d = bfs(make_pair(i, j), en);
            ans = min(ans, d);
        }
    }
    cout << ans << endl;

    return 0;
}
