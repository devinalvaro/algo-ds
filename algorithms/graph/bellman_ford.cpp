/* Bellman Ford's algorithm to detect negative weight cycle in a graph */

#include <map>
#include <vector>

using namespace std;

/**
 * n: number of nodes in graph [1...n]
 * s: starting node
 * edges: edges[u][j] = <d, v>, where v is a neighbor of u
 *                                    d is the weight of edge connecting u and v
 * dist: resulting vector where distance[e] is distance of e from s
 */
void bellman_ford(int n, int s, map<int, vector<pair<int, int>>> &edges,
                  vector<int> &dist)
{
    dist[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int u = 1; u <= n; u++) {
            for (size_t j = 0; j < edges[u].size(); j++) {
                int v = edges[u][j].second;
                int d = edges[u][j].first;

                dist[v] = min(dist[v], dist[u] + d);
            }
        }
    }
}

/**
 * n: number of nodes in graph [1...n]
 * edges: edges[u][j] = <d, v>, where v is a neighbor of u
 * dist: resulting vector where distance[e] is distance of e from s
 */
bool has_negative_cycle(int n, map<int, vector<pair<int, int>>> &edges,
                        const vector<int> &dist)
{
    for (int u = 1; u <= n; u++) {
        for (size_t j = 0; j < edges[u].size(); j++) {
            int v = edges[u][j].second;
            int d = edges[u][j].first;

            if (dist[v] > dist[u] + d) {
                return true;
            }
        }
    }
    return false;
}
