/* Floyd Warshall's algorithm to find all-pair shortest paths *
 * with a function to find the shortest paths */

#include <vector>

using namespace std;

/**
 * n: number of nodes in graph [1...n]
 * adjacent: adjacent[i][j] will be the shortest distance between i and j
 * parent: parent[i][j] is the last node before j on a shortest path from i to j
 */
void floyd_warshall(int n, vector<vector<int>> &adjacent,
                    vector<vector<int>> &parent)
{
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            parent[i][j] = i;
        }
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (adjacent[i][k] + adjacent[k][j] < adjacent[i][j]) {
                    adjacent[i][j] = adjacent[i][k] + adjacent[k][j];

                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
}

/**
 * parent: parent[i][j] is the last node before j on a shortest path from i to j
 * i: starting node int he path
 * j: end node in the path
 * shortest_path: resulting aray of nodes on a shortest path from i to j
 */
void find_path(const vector<vector<int>> &parent, int i, int j,
               vector<int> &shortest_path)
{
    if (i != j) {
        find_path(parent, i, parent[i][j], shortest_path);
    }

    shortest_path.push_back(j);
}
