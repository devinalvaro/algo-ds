/* Topological Sort for directed acyclic graph */

#include <vector>

using namespace std;

void topo_sort(const vector<vector<int>> &edges, vector<bool> &visited, int u,
               vector<int> topo_array) {
    visited[u] = true;

    for (size_t j = 0; j < edges[u].size(); j++) {
        int v = edges[u][j];

        if (!visited[v]) {
            topo_sort(edges, visited, v, topo_array);
        }
    }

    topo_array.push_back(u);
}
