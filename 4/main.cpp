#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cstring>
using namespace std;

vector<string> split(string s, string sep) {
    vector<string> res;
    size_t pos = 0;
    while (pos != string::npos) {
        size_t new_pos = s.find(sep, pos);
        res.push_back(s.substr(pos, new_pos));
        pos = new_pos;
        if (pos != string::npos) {
            pos += sep.size();
        }
    }
    return res;
}

pair<int, int> parse_pair(string s) {
    auto parts = split(s, "-");
    assert(parts.size() == 2);
    return {stoi(parts[0]), stoi(parts[1])};
}

int main() {
    string s;

    int ans = 0;
    while (cin >> s) {
        auto parts = split(s, ",");
        assert(parts.size() == 2);

        auto[x1, y1] = parse_pair(parts[0]);
        auto[x2, y2] = parse_pair(parts[1]);

        /*
        auto contains = [](int x1, int y1, int x2, int y2) {
            return x1 <= x2 && y1 >= y2;
        };
        if (contains(x1, y1, x2, y2) || contains(x2, y2, x1, y1)) {
            ans++;
        }
        */

        auto overlaps = [](int x1, int y1, int x2, int y2) {
            return x1 <= x2 && x2 <= y1;
        };
        if (overlaps(x1, y1, x2, y2) || overlaps(x2, y2, x1, y1)) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
