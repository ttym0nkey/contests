#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <limits>
#include <cassert>
#include <fstream>
#include <array>

using namespace std;

#define endl '\n'

int allRed = 0;
int allBlue = 0;
 int result = 0;


void Dfs(const vector<vector<int>>& graph, const vector<int>& colors, vector<bool> &visited, vector<pair<int, int>>& redBlueCount, int v) {
    if (colors[v] == 1) {
        redBlueCount[v].first = 1;
    } else if (colors[v] == 2) {
        redBlueCount[v].second = 1;
    }

    visited[v] = true;

    for (const auto n: graph[v]) {
        if (visited[n]) {
            continue;
        }

        Dfs(graph, colors, visited, redBlueCount, n);

        if (redBlueCount[n].first == allRed && redBlueCount[n].second == 0) {
            ++result;
        }

        if (redBlueCount[n].first == 0 && redBlueCount[n].second == allBlue) {
            ++result;
        }

        redBlueCount[v].first += redBlueCount[n].first;
        redBlueCount[v].second += redBlueCount[n].second;
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.precision(10);

    int n, v, u;
    cin >> n;

    vector<pair<int, int>> edges;
    vector<vector<int>> graph(n, vector<int>());
    vector<int> colors(n);
    vector<pair<int, int>> redBlueCount(n);
    vector<bool> visited(n, false);

    for (size_t i = 0; i < n; ++i) {
        cin >> colors[i];

        if (colors[i] == 1) {
            ++allRed;
        } else if (colors[i] == 2) {
            ++allBlue;
        }
    }

    for (size_t i = 0; i < n - 1; ++i) {
        cin >> v >> u;
        --v;
        --u;

        edges.emplace_back(v, u);

        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    Dfs(graph, colors, visited, redBlueCount, 0);

    cout << result << endl;

    return 0;
}
