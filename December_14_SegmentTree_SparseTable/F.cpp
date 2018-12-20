#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

template <class T>
vector<int> compress(vector<T> values) {
    vector<T> sorted = values; // copying
    sort(sorted.begin(), sorted.end());
    sorted.resize(unique(sorted.begin(), sorted.end()) - sorted.begin());

    vector<int> result(values.size());
    for (int i = 0; i < values.size(); ++i) {
        result[i] = lower_bound(sorted.begin(), sorted.end(), values[i]) - sorted.begin();
    }

    return result;
}

const int BASE = 1000'000'000 + 7;
const int MODULO = 1000'000'000 + 31;

inline int add(int a, int b) {
    return (a + b) % MODULO;
}
//
//inline ll subtract(ll a, ll b) {
//    return add(a, MODULO - b % MODULO);
//}

inline int multiply(ll a, ll b) {
    return (int)((a * b) % MODULO);
}

inline int shifted_add(int left, int shift, int right) {
    return add(multiply(left, shift), right);
}

class SegmentTree {

public:

    size_t size;

    vector<int> values;

    vector<char> lazy;
    vector<int> colors;

    vector<int> hashBases;
    vector<int> shifts;

    SegmentTree(size_t n)
            : size(n)
            , values(size << 2, 0)
            , lazy(size << 2, false)
            , colors(size << 2, 0)
            , hashBases(size << 2, 1)
            , shifts(size << 2, BASE)
    { }

    int get_vertex(int v) {
        return add(values[v], multiply(colors[v], hashBases[v]));
    }

    void set_vertex(int v, int value) {
        lazy[v] = true;
        colors[v] = value;
        values[v] = 0;
    }

    void push_vertex(int v, int vL, int vR) {
        if (lazy[v]) {
            set_vertex(vL, colors[v]);
            set_vertex(vR, colors[v]);

            colors[v] = 0;
            lazy[v] = false;
        }
    }

    void update_vertex(int v, int vL, int vR) {
        values[v] = multiply(get_vertex(vL), shifts[vR]);
        values[v] = add(values[v], get_vertex(vR));
    }

    vector<int> a;
    void build(vector<int> _a) {
        a = _a;
        build_tree(1, 0, size);
    }

    void build_tree(int v, int l, int r) {
        if (l + 1 == r) {
            values[v] = a[l];
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            build_tree(vL, l, m);
            build_tree(vR, m, r);

            shifts[v] = multiply(shifts[vL], shifts[vR]);
            hashBases[v] = shifted_add(hashBases[vL], shifts[vR], hashBases[vR]);
            values[v] = shifted_add(values[vL], shifts[vR], values[vR]);
        }
    }

    int start, end;
    int value;

    void update_segment(int _start, int _end, int _value) {
        start = _start;
        end = _end + 1;
        value = _value;

        update_tree(1, 0, size);
    }

    void update_tree(int v, int l, int r) {
        if (start <= l && r <= end) {
            set_vertex(v, value);
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            push_vertex(v, vL, vR);

            if (start < m) update_tree(vL, l, m);
            if (m < end) update_tree(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }

    int res;

    int get_interval(int _start, int _end) { // [start; end)
        start = _start;
        end = _end;

        res = 0;

        get_tree_segment(1, 0, size);

        return res;
    }

    void get_tree_segment(int v, int l, int r) {
        if (start <= l && r <= end) {
            res = shifted_add(res, shifts[v], get_vertex(v));
        } else {
            int m = (l + r) >> 1;
            int vL = (v << 1), vR = (vL + 1);

            push_vertex(v, vL, vR);

            if (start < m) get_tree_segment(vL, l, m);
            if (m < end) get_tree_segment(vR, m, r);

            update_vertex(v, vL, vR);
        }
    }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegmentTree tree(n);
    tree.build(a);

    size_t q;
    cin >> q;

    vector<char> answers;

    for (int query = 0; query < q; ++query) {
        int type, left, right, value;
        cin >> type >> left >> right >> value;

        left--, right--;

        if (type == 0) {
            tree.update_segment(left, right, value);
        } else {
            ll left_hash = tree.get_interval(left, left + value);
            ll right_hash = tree.get_interval(right, right + value);

            bool answer = left_hash == right_hash;
            answers.push_back(answer);
        }
    }

    for (bool answer : answers) {
        cout << (answer ? '+' : '-');
    }
    cout << endl;

    return 0;
}