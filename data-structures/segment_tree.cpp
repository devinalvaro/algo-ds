/* Segment Tree for range sum query with lazy propagation */

#include <vector>

using namespace std;

class SegmentTree {
private:
    int n;
    vector<int> arr;
    vector<int> segment_tree;
    vector<int> lazy;

    int left_child(int parent) { return (parent << 1) + 1; }

    int right_child(int parent) { return (parent << 1) + 2; }

    void build(int parent, int left, int right) {
        if (left > right)
            return;

        if (left == right) {
            segment_tree[parent] = arr[left];

            return;
        }

        int mid = (left + right) / 2;
        build(left_child(parent), left, mid);
        build(right_child(parent), mid + 1, right);

        segment_tree[parent] = segment_tree[left_child(parent)] +
                               segment_tree[right_child(parent)];
    }

    int query(int parent, int left, int right, int i, int j) {
        if (lazy[parent] != 0) {
            segment_tree[parent] += (right - left + 1) * lazy[parent];

            if (left != right) {
                lazy[left_child(parent)] += lazy[parent];
                lazy[right_child(parent)] += lazy[parent];
            }

            lazy[parent] = 0;
        }

        if (left > right || left > j || right < i)
            return 0;

        if (left >= i && right <= j) {
            return segment_tree[parent];
        }

        int mid = (left + right) / 2;
        return query(left_child(parent), left, mid, i, j) +
               query(right_child(parent), mid + 1, right, i, j);
    }

    void update_range(int parent, int left, int right, int i, int j, int diff) {
        if (lazy[parent] != 0) {
            segment_tree[parent] += (right - left + 1) * lazy[parent];

            if (left != right) {
                lazy[left_child(parent)] += lazy[parent];
                lazy[right_child(parent)] += lazy[parent];
            }

            lazy[parent] = 0;
        }

        if (left > right || left > j || right < i)
            return;

        if (left >= i && right <= j) {
            segment_tree[parent] += (right - left + 1) * diff;

            if (left != right) {
                lazy[left_child(parent)] += diff;
                lazy[right_child(parent)] += diff;
            }

            return;
        }

        int mid = (left + right) / 2;
        update_range(left_child(parent), left, mid, i, j, diff);
        update_range(right_child(parent), mid + 1, right, i, j, diff);

        segment_tree[parent] = segment_tree[left_child(parent)] +
                               segment_tree[right_child(parent)];
    }

public:
    SegmentTree(int _n, vector<int> &_arr) {
        n = _n;
        arr = _arr;

        segment_tree.assign(4 * n, 0);
        build(0, 0, n - 1);

        lazy.assign(4 * n, 0);
    }

    int query(int i, int j) { return query(0, 0, n - 1, i, j); }

    void update_range(int i, int j, int diff) {
        update_range(0, 0, n - 1, i, j, diff);
    }
};
