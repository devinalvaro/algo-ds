/* Dijkstra's algorithm to find single source shortest path in a graph */

#include <climits>
#include <map>
#include <queue>
#include <vector>

using namespace std;

/**
 * n: number of nodes in graph [1...n]
 * s: starting node
 * edges: edges[u][j] = v means u is adjacent or neighbor with v
 * dist: resulting vector where distance[e] is distance of e from s
 */
void dijkstra(int n, int s, map<int, vector<pair<int, int>>> &edges,
              vector<int> &dist) {
    dist.assign(n + 1, INT_MAX);
    dist[s] = 0; // start at node s

    // priority queue of <dist[node], node> with nearest node on top
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        pq;
    pq.push(pair<int, int>(dist[s], s));

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u])
            continue; // lazy deletion

        for (size_t j = 0; j < edges[u].size(); j++) {
            int v = edges[u][j].second;
            int d = edges[u][j].first;

            if (dist[u] + d < dist[v]) {
                dist[v] = dist[u] + d;

                pq.push(pair<int, int>(dist[v], v));
            }
        }
    }
}
