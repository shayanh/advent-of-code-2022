#include <iostream>
using namespace std;

char get_play(char a, char b) {
    if (b == 'X') {
        if (a == 'A') return 'Z';
        if (a == 'B') return 'X';
        if (a == 'C') return 'Y';
    } else if (b == 'Y') {
        if (a == 'A') return 'X';
        if (a == 'B') return 'Y';
        if (a == 'C') return 'Z';
    } else if (b == 'Z') {
        if (a == 'A') return 'Y';
        if (a == 'B') return 'Z';
        if (a == 'C') return 'X';
    }
    throw "fuck";
}

int get_result(char a, char b) {
    int res = 0;

    if (b == 'X') {
        res += 1;
    } else if (b == 'Y') {
        res += 2;
    } else if (b == 'Z') {
        res += 3;
    }

    if ((a == 'A' && b == 'X') || (a == 'B' && b == 'Y') || (a == 'C' && b == 'Z')) {
        res += 3;
    }

    if ((a == 'A' && b == 'Y') || (a == 'B' && b == 'Z') || (a == 'C' && b == 'X')) {
        res += 6;
    }

    return res;
}

int main() {
    char a, b;

    int ans = 0;
    while (cin >> a >> b) {
        //ans += get_result(a, b);
        
        char c = get_play(a, b);
        ans += get_result(a, c);
    }
    cout << ans << endl;
}
