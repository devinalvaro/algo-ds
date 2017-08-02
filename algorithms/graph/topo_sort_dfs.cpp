/* Topological Sort with depth-first search for directed acyclic graph */

#include <map>
#include <vector>

using namespace std;

/**
 * edges: edges[u][j] = v means u is adjacent or neighbor with v
 * visited: visited[u] = true means u has been visited
 * u: index of current node (1 <= u <= N)
 * topo_array: resulting array of topologically sorted elements
 */
void topo_sort(map<int, vector<int>> &edges, vector<bool> &visited, int u,
               vector<int> topo_array)
{
    visited[u] = true;

    for (size_t j = 0; j < edges[u].size(); j++) {
        int v = edges[u][j];

        if (!visited[v]) {
            topo_sort(edges, visited, v, topo_array);
        }
    }

    topo_array.push_back(u);
}
