#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int score(char c) {
    if (islower(c)) {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

int solve1(string &s) {
    map<char, bool> m1, m2;

    int m = s.size() / 2;

    for (int i = 0; i < m; i++) {
        m1[s[i]] = true;
    }
    for (int i = m; i < s.size(); i++) {
        m2[s[i]] = true;
    }

    for (int i = 0; i < s.size(); i++) {
        if (m1[s[i]] && m2[s[i]]) {
            return score(s[i]);
        }
    }
}

int solve2(vector<string> &ss) {
    int res = 0;
    for (int i = 0; i < ss.size(); i+= 3) {
        map<char, bool> m[3];

        for (int j = 0; j < 3; j++) {
            for (char c: ss[i+j]) {
                m[j][c] = true;
            }
        }

        auto check = [&m](char c) {
            return m[0][c] && m[1][c] && m[2][c];
        };

        res += [&check]() {
            for (int k = 0; k < 26; k++) {
                if (check(k+'a')) {
                    return score(k+'a');
                }
                if (check(k+'A')) {
                    return score(k+'A');
                }
            }
        }();
    }
    return res;
}

int main() {
    string s;
    int ans = 0;

    vector<string> ss;
    while (cin >> s) {
        ss.push_back(s);
        //ans += solve1(s);
    }
    ans = solve2(ss);
    cout << ans << endl;

    return 0;
}
