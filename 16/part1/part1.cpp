#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

vector<string> split(string s, string sep) {
    vector<string> res;
    size_t pos = 0;
    while (pos != string::npos) {
        size_t new_pos = s.find(sep, pos);
        res.push_back(s.substr(pos, new_pos-pos));
        pos = new_pos;
        if (pos != string::npos) {
            pos += sep.size();
        }
    }
    return res;
}

const int MAXT = 31;
const int MAXN = 60;

map<string, int> valves;
int rates[MAXN];
vector<string> adj[MAXN];
vector<int> non_zero;

void parse_line(string s) {
    auto parts = split(s, " ");

    string valve = parts[1];
    int idx = valves.size();
    valves[valve] = idx;

    int r = stoi(parts[4].substr(5, parts[4].size()-1));
    rates[idx] = r;

    if (r > 0) {
        non_zero.push_back(idx);
    }

    for (size_t i = 9; i < parts.size(); i++) {
        string t = parts[i];
        if (t.ends_with(",")) {
            t = t.substr(0, t.size() - 1);
        }
        adj[idx].push_back(t);
    }
}

const int MAX_MASK = 1 << 16;
const int T = 30;

int dp[MAXT][MAXN][MAX_MASK];

int get_mask_pressure(int mask) {
    int res = 0;
    for (size_t i = 0; i < non_zero.size(); i++) {
        if ((mask & (1 << i)) != 0) {
            res += rates[non_zero[i]];
        }
    }
    return res;
}

int solve(int t, int x, int mask) {
    if (t > T) {
        return 0;
    }
    if (dp[t][x][mask] != -1) {
        return dp[t][x][mask];
    }

    int ret = solve(t+1, x, mask);
    int pressure = get_mask_pressure(mask);

    if (rates[x] > 0) {
        int pos = find(non_zero.begin(), non_zero.end(), x) - non_zero.begin();
        if ((mask & (1 << pos)) == 0) {
            int new_mask = mask ^ (1 << pos);
            int curr = pressure + solve(t+1, x, new_mask);
            ret = max(ret, curr);
        }
    }

    for (auto vstr: adj[x]) {
        int v = valves[vstr];
        int curr = pressure + solve(t+1, v, mask);
        ret = max(ret, curr);
    }

    dp[t][x][mask] = ret;
    return ret;
}

int main() {
    string s;
    while (getline(cin, s)) {
        parse_line(s);
    }

    memset(dp, -1, sizeof dp);

    int ans = solve(1, valves["AA"], 0);
    cout << ans << endl;
}
