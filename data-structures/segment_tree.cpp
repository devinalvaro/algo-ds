/* Segment Tree for range sum query with lazy propagation */

#include <vector>

using namespace std;

class SegmentTree {
private:
    vector<int> arr, lazy, st;

    int left(int id) {
        return (id << 1) + 1;
    }

    int right(int id) {
        return (id << 1) + 2;
    }

    void build(int id, int l, int r) {
        if (l > r) {
            return;
        }
        if (l == r) {
            st[id] = arr[l];
            return;
        }

        int m = (l + r) / 2;
        build(left(id), l, m);
        build(right(id), m + 1, r);
        st[id] = st[left(id)] + st[right(id)];
    }

    int query(int id, int l, int r, int lq, int rq) {
        lazy_update(id, l, r);

        if (l > r || r < lq || rq < l) {
            return 0;
        }
        if (lq <= l && r <= rq) {
            return st[id];
        }

        int m = (l + r) / 2;
        return query(left(id), l, m, lq, rq) +
               query(right(id), m + 1, r, lq, rq);
    }

    void update(int id, int l, int r, int lq, int rq, int diff) {
        lazy_update(id, l, r);

        if (l > r || r < lq || rq < l) {
            return;
        }
        if (lq <= l && r <= rq) {
            st[id] += (r - l + 1) * diff;

            if (l != r) {
                lazy[left(id)] += diff;
                lazy[right(id)] += diff;
            }
            return;
        }

        int m = (l + r) / 2;
        update(left(id), l, m, lq, rq, diff);
        update(right(id), m + 1, r, lq, rq, diff);
        st[id] = st[left(id)] + st[right(id)];
    }

    void lazy_update(int id, int l, int r) {
        if (lazy[id] == 0) {
            return;
        }

        st[id] += (r - l + 1) * lazy[id];

        if (l != r) {
            lazy[left(id)] += lazy[id];
            lazy[right(id)] += lazy[id];
        }
        lazy[id] = 0;
    }

public:
    SegmentTree(vector<int> &_arr) {
        arr = _arr;

        st.assign(4 * arr.size(), 0);
        build(0, 0, arr.size() - 1);

        lazy.assign(4 * arr.size(), 0);
    }

    int query(int lq, int rq) {
        return query(0, 0, arr.size() - 1, lq, rq);
    }

    void update(int lq, int rq, int diff) {
        update(0, 0, arr.size() - 1, lq, rq, diff);
    }
};
