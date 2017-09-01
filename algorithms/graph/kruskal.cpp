/* Kruskal algorithm to find minimum spanning tree with UFDS */

#include <algorithm>
#include <vector>

#include "../../data-structures/ufds.cpp"

/**
 * n: number of nodes in graph [1...n]
 * edges_list: list of edges, where edges[i].second.first is the first node
 *                                  edges[i].second.second is the second node
 *                                  edges[i].first is distance between the two
 */
int kruskal(int n, vector<pair<int, pair<int, int>>> &edges_list)
{
    sort(edges_list.begin(), edges_list.end());

    UFDS ufds(n);
    int mst_cost = 0;

    for (size_t i = 0; i < edges_list.size(); i++) {
        int u = edges_list[i].second.first;
        int v = edges_list[i].second.second;
        int w = edges_list[i].first;

        if (ufds.find(u) != ufds.find(v)) {
            ufds.merge(u, v);

            mst_cost += w;
        }
    }

    return mst_cost;
}
