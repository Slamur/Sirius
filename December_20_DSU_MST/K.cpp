#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>

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

struct DSU {
    vector<int> parents;
    vector<int> xors;

    vector<vector<int>> components;
    vector<unordered_map<int, int>> xor_counts;

    ll bad_pairs;

    DSU(size_t n)
            : parents(n)
            , xors(n, 0)
            , components(n)
            , xor_counts(n)
            , bad_pairs(0)
    {
        for (int v = 0; v < n; ++v) {
            parents[v] = v;
            components[v] = { v };
            xor_counts[v][0] = 1;
        }
    }

    int get(int v) {
        int  parent = parents[v];
        if (parent == v) return v;

        parents[v] = get(parent);
        xors[v] ^= xors[parent];

        return parents[v];
    }

    int get_xor(int v) {
        get(v);
        return xors[v];
    }

    bool merge(int f, int t, int value) {
        int a = get(f);
        int b = get(t);

        if (a == b) return false;

        if (components[a].size() < components[b].size()) {
            swap(a, b);
        }


        vector<int> & compA = components[a];
        vector<int> & compB = components[b];

        int ab_xor = get_xor(f) ^ value ^ get_xor(t);

        for (int v : compB) {
            int v_xor = get_xor(v) ^ ab_xor;
            bad_pairs += xor_counts[a][v_xor];
        }

        for (int v : compB) {
            compA.push_back(v);

            int v_xor = xors[v] ^ ab_xor;
            xor_counts[a][v_xor]++;
        }

        parents[b] = a;
        xors[b] = ab_xor;
    }
};

typedef pair<int, pair<int, int>> edge;

int main() {
    size_t n;
    cin >> n;

    size_t m = n - 1;

    vector<edge> edges(m);
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        --from, --to;

        edges[i] = { weight, { from, to } };
    }

    vector<int> permutation(m);
    for (int i = 0; i < m; ++i) {
        cin >> permutation[i];
        --permutation[i];
    }

    DSU dsu(n);

    vector<ll> answers(m + 1, 0);
    for (int i = m - 1; i >= 0; --i) {
        edge & e = edges[permutation[i]];
        dsu.merge(e.second.first, e.second.second, e.first);
        answers[i] = dsu.bad_pairs;
    }

    for (ll answer : answers) {
        cout << answer << '\n';
    }

    return 0;
}