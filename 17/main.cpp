#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<string> shape;

const int MAXS = 10;
const int MAXJ = 20000;

bool mark[MAXS][MAXJ];

int main() {
    string jet;
    cin >> jet;

    int jet_idx = 0;
    
    vector<shape> shapes = {
        {
            "####"
        },
        {
            ".#.",
            "###",
            ".#."
        },
        {
            "..#",
            "..#",
            "###",
        },
        {
            "#",
            "#",
            "#",
            "#",
        },
        {
            "##",
            "##",
        },
    };

    vector<string> m;

    auto place = [&m](int y, int x, shape s) {
        //cerr << y << ' ' << x << endl;

        int y_offset = 0;
        for (int i = s.size()-1; i >= 0; i--) {
            for (int j = 0; j < (int)s[i].size(); j++) {
                if (m[y + y_offset][j+x] == '#' && s[i][j] == '#') {
                    assert(false);
                }
                
                if (m[y + y_offset][j+x] == '.') {
                    m[y + y_offset][j+x] = s[i][j];
                }
            }
            y_offset += 1;
        }
    };

    auto has_conflict = [&m](int y, int x, shape s) {
        int y_offset = 0;
        for (int i = s.size()-1; i >= 0; i--) {
            for (int j = 0; j < (int)s[i].size(); j++) {
                if (m[y + y_offset][j+x] == '#' && s[i][j] == '#') {
                    return true;
                }
            }
            y_offset += 1;
        }
        return false;
    };

    auto move_down = [&has_conflict](int y, int x, shape s) {
        if (y == 0) {
            return false;
        }

        return !has_conflict(y-1, x, s);
    };

    auto move_left = [&has_conflict](int y, int x, shape s) {
        if (x == 0) {
            return false;
        }
        return !has_conflict(y, x-1, s);
    };

    auto move_right = [&has_conflict](int y, int x, shape s) {
        if ((x + s[0].size()) > 6) {
            return false;
        }
        return !has_conflict(y, x+1, s);
    };

    function<void(int, int, shape, int)> rock_fall = [&place, &rock_fall, &jet, &jet_idx, &move_left, &move_right, &move_down, &shapes]
        (int y, int x, shape s, int shape_idx) {
        //cerr << y << ' ' << x << ' ' << jet_idx << ' ' << jet[jet_idx] << endl;

        int sm = shape_idx % shapes.size();
        int jm = jet_idx % jet.size();
        if (mark[sm][jm]) {
            cerr << shape_idx << ' ' << jet_idx << endl;
        }
        mark[sm][jm] = true;

        if (jet[jet_idx % jet.size()] == '<') {
            bool b = move_left(y, x, s);
            if (b) {
                x--;
            }
        } else if (jet[jet_idx % jet.size()] == '>') {
            bool b = move_right(y, x, s);
            if (b) {
                x++;
            }
        }
        jet_idx++;

        bool ok = move_down(y, x, s);
        if (!ok) {
            place(y, x, s);
            return ;
        } else {
            rock_fall(y-1, x, s, shape_idx);
        }
    };

    int h = 0;

    auto updateh = [&m, &h]() {
        while (m[h].find('#') != string::npos) {
            h++;
        }
    };

    //int N = 2022;
    int N = 200000;
    for (int f = 0; f < N; f++) {
        if (f % shapes.size() == 0 && jet_idx % jet.size() == 0) {
            cout << f << endl;
        }

        for (int i = 0; i < 5; i++) {
            m.push_back(".......");
        }
        rock_fall(h+3, 2, shapes[f % shapes.size()], f);

        updateh();
    }

    //auto printm = [&m, &h]() {
        //for (int i = h; i >= 0; i--) {
            //cout << m[i] << endl;
        //}
    //};
    //printm();

    cout << h << endl;
    return 0;
}

