#include <iostream>
#include <string>
#include <set>
#include <cstdlib>
#include <vector>
using namespace std;

#define X first
#define Y second

set<pair<int, int> > mark;

int N = 10;
vector<pair<int, int> > rope;

int calc_dis(int i) {
    return abs(rope[i].X - rope[i+1].X) + abs(rope[i].Y - rope[i+1].Y);
}

void smove(int i) {
    auto get_dir = [](int a, int b) {
        if (a > b) {
            return +1;
        }
        if (a < b) {
            return -1;
        }
        return 0;
    };

    if (rope[i].X == rope[i+1].X || rope[i].Y == rope[i+1].Y) {
        int dis = calc_dis(i);
        if (dis < 2) {
            return ;
        }

        rope[i+1].X += get_dir(rope[i].X, rope[i+1].X);
        rope[i+1].Y += get_dir(rope[i].Y, rope[i+1].Y);
    } else {
        int dis = calc_dis(i);
        if (dis == 2) {
            return ;
        }

        rope[i+1].X += get_dir(rope[i].X, rope[i+1].X);
        rope[i+1].Y += get_dir(rope[i].Y, rope[i+1].Y);
    }
}

void mmove(char d) {
    if (d == 'D') {
        rope[0].X++;
    }
    if (d == 'U') {
        rope[0].X--;
    }
    if (d == 'R') {
        rope[0].Y++;
    }
    if (d == 'L') {
        rope[0].Y--;
    }

    for (int i = 0; i < N-1; i++) {
        smove(i);
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        rope.push_back({0, 0});
    }
    mark.insert(rope[N-1]);

    char d; int c;
    while (cin >> d >> c) {
        while (c--) {
            mmove(d);

            //cerr << d << ' ' << c << endl;
            //for (int i = 0; i < N; i++) {
                //cerr << rope[i].X << ' ' << rope[i].Y << endl;
            //}

            mark.insert(rope[N-1]);
        }
    }

    cout << mark.size() << endl;
    return 0; 
}
