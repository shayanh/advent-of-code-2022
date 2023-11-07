#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define VAL(x) #x << " = " << (x) << "   "

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

struct Blueprint {
    Blueprint(int ore_cost, int clay_cost, pair<int, int> obisidian_cost, pair<int, int> geode_cost): 
        ore_robot_cost(ore_cost), clay_robot_cost(clay_cost), 
        obisidian_robot_cost(obisidian_cost), geode_robot_cost(geode_cost) {}

    int ore_robot_cost;
    int clay_robot_cost;
    pair<int, int> obisidian_robot_cost;
    pair<int, int> geode_robot_cost;
};

const int K = 8;
const int K2 = 25;
const int T = 24;

int dp[T][K][K][K][K][K][K2][K2];

int solve(const Blueprint& b, int t, int ore_robots, int clay_robots, int obisidian_robots, 
          int geode_robots, int ore, int clay, int obisidian) {
    if (t >= T) {
        return 0;
    }
    //if (ore_robots >= K || clay_robots >= K || obisidian_robots >= K || geode_robots >= K || ore >= K || clay >= K2 || obisidian >= K2) {
        //return (T - t) * geode_robots;
    //}

    ore_robots = min(ore_robots, K-1);
    clay_robots = min(clay_robots, K-1);
    obisidian_robots = min(obisidian_robots, K-1);
    geode_robots = min(geode_robots, K-1);

    ore = min(ore, K-1);
    clay = min(clay, K2-1);
    obisidian = min(obisidian, K2-1);

    int &h = dp[t][ore_robots][clay_robots][obisidian_robots][geode_robots][ore][clay][obisidian];
    if (h != -1) {
        return h;
    }

    //cerr << VAL(t) << VAL(ore_robots) << VAL(clay_robots) << VAL(obisidian_robots) << VAL(geode_robots) << endl;

    int ret = 0;
    if (ore >= b.ore_robot_cost) {
        int next_ore = ore - b.ore_robot_cost + ore_robots;
        int next_clay = clay + clay_robots;
        int next_obidisian = obisidian + obisidian_robots;
        int next_geode = geode_robots;

        int curr = solve(b, t+1, ore_robots+1, clay_robots, obisidian_robots, geode_robots,
                         next_ore, next_clay, next_obidisian);
        ret = max(ret, curr + next_geode);
    }
    if (ore >= b.clay_robot_cost) {
        int next_ore = ore - b.clay_robot_cost + ore_robots;
        int next_clay = clay + clay_robots;
        int next_obidisian = obisidian + obisidian_robots;
        int next_geode = geode_robots;

        int curr = solve(b, t+1, ore_robots, clay_robots+1, obisidian_robots, geode_robots,
                         next_ore, next_clay, next_obidisian);
        ret = max(ret, curr + next_geode);
    }
    if (ore >= b.obisidian_robot_cost.first && clay >= b.obisidian_robot_cost.second) {
        int next_ore = ore - b.obisidian_robot_cost.first + ore_robots;
        int next_clay = clay - b.obisidian_robot_cost.second + clay_robots;
        int next_obidisian = obisidian + obisidian_robots;
        int next_geode = geode_robots;

        int curr = solve(b, t+1, ore_robots, clay_robots, obisidian_robots+1, geode_robots,
                         next_ore, next_clay, next_obidisian);
        ret = max(ret, curr + next_geode);
    }
    if (ore >= b.geode_robot_cost.first && obisidian >= b.geode_robot_cost.second) {
        int next_ore = ore - b.geode_robot_cost.first + ore_robots;
        int next_clay = clay + clay_robots;
        int next_obidisian = obisidian - b.geode_robot_cost.second + obisidian_robots;
        int next_geode = geode_robots;

        int curr = solve(b, t+1, ore_robots, clay_robots, obisidian_robots, geode_robots+1,
                         next_ore, next_clay, next_obidisian);
        ret = max(ret, curr + next_geode);
    }
    {
        int next_ore = ore + ore_robots;
        int next_clay = clay + clay_robots;
        int next_obidisian = obisidian + obisidian_robots;
        int next_geode = geode_robots;

        int curr = solve(b, t+1, ore_robots, clay_robots, obisidian_robots, geode_robots,
                         next_ore, next_clay, next_obidisian);
        ret = max(ret, curr + next_geode);
    }

    h = ret;
    return ret;
}

int main() {
    int idx = 0, ans = 0;

    string s;
    while (getline(cin, s)) {
        auto parts = split(s, " ");
        
        int ore_cost = stoi(parts[6]);
        int clay_cost = stoi(parts[12]);
        pair<int, int> obisidian_cost = make_pair(stoi(parts[18]), stoi(parts[21]));
        pair<int, int> geode_cost = make_pair(stoi(parts[27]), stoi(parts[30]));

        //cerr << ore_cost << ' ' << clay_cost << endl;
        //cerr << obisidian_cost.first << ' ' << obisidian_cost.second << endl;
        //cerr << geode_cost.first << ' ' << geode_cost.second << endl;

        Blueprint b = Blueprint(ore_cost, clay_cost, obisidian_cost, geode_cost);

        memset(dp, -1, sizeof dp);
        int res = solve(b, 0, 1, 0, 0, 0, 0, 0, 0);

        ans += (idx+1) * res;

        idx++;
    }

    cout << ans << endl;
    return 0;
}
