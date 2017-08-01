/* Topological Sort with breadth-first search for directed acyclic graph */

#include <map>
#include <queue>
#include <vector>

using namespace std;

/**
 * n: number of elements to topologically sorted [1...n]
 * edges: edges[u][j] = v means u is adjacent or neighbor with v
 * in_degrees: in_degrees[u] means number of nodes adjacent with u
 * topo_array: resulting array of topologically sorted elements
 */
void topo_sort_bfs(int n, map<int, vector<int>> &edges, vector<int> &in_degrees,
                   vector<int> &topo_array) {
    // priority queue with minimum element on top
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (in_degrees[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        topo_array.push_back(u);

        for (size_t j = 0; j < edges[u].size(); j++) {
            int v = edges[u][j];

            in_degrees[v]--;
            if (in_degrees[v] == 0) {
                pq.push(v);
            }
        }
    }
}
