#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    string s;
    int curr = 0;
    vector<int> v;
    while (getline(cin, s)) {
        if (s == "") {
            v.push_back(curr);
            curr = 0;
        } else {
            int n = stoi(s);
            curr += n;
        }
    }

    sort(v.begin(), v.end(), greater<int>());
    int ans = v[0] + v[1] + v[2];
    cout << ans << endl;
    return 0;
}
