#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;

template <class T>
void read(size_t size, vector<T> & a){
    a.resize(size);
    for (T & value : a) cin >> value;
}

const char SPACE = ' ', ENDL = '\n';

template <class T>
void print(vector<T> & a, char sep = SPACE) {
    for (T & value : a) cout << value << sep;
    cout << '\n';
}

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

int get_bit(ll mask, int bit) {
    return (int)((mask >> bit) & 1);
}

string reverse(string s) {
    reverse(s.begin(), s.end());
    return s;
}

vector<int> reverse(vector<int> a) {
    reverse(a.begin(), a.end());
    return a;
}

vector<int> concat_separated(vector<int> & a, vector<int> & b, int sep = -1) {
    size_t n = a.size(), m = b.size();
    vector<int> s(n + 1 + m);
    for (int i = 0; i < n; ++i) s[i] = a[i];
    s[n] = sep;
    for (int j = 0; j < m; ++j) s[n + 1 + j] = b[j];
    return s;
}

const int BASE = 1000'000'000 + 7;
const int MODULO = 1000'000'000 + 31;

template <int modulo>
inline int add(int a, int b) {
    return (a + b) % modulo;
}

template <int modulo>
inline int subtract(int a, int b) {
    return add<modulo>(a, modulo - b);
}

template <int modulo>
inline int multiply(ll a, ll b) {
    return (int)((a * b) % modulo);
}

struct DSU {
    vector<int> parents;
    vector<int> ranks;

    DSU(size_t n)
            : parents(n)
            , ranks(n, 1)
    {
        for (int v = 0; v < n; ++v) {
            parents[v] = v;
        }
    }

    int get(int v) {
        int parent = parents[v];
        if (parent == v) return v;

        return parents[v] = get(parent);
    }

    bool merge(int f, int t) {
        int a = get(f);
        int b = get(t);

        if (a == b) return false;

        if (ranks[a] < ranks[b]) {
            swap(a, b);
        }

        parents[b] = a;
        if (ranks[a] == ranks[b]) ++ranks[a];

        return true;
    }
};

typedef pair<int, int> edge;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n, m;
    cin >> n >> m;

    DSU dsu(n);

    vector<edge> answer;
    for (int i = 0; i < m; ++i) {
        int from, to;
        cin >> from >> to;
        --from, --to;

        if (dsu.merge(from, to)) {
            answer.push_back({ from, to });
        }
    }

    for (auto & edge : answer) {
        cout << edge.first + 1 << " " << edge.second + 1 << ENDL;
    }

    return 0;
}