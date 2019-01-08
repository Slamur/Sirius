#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <ctime>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<size_t> vsz;

typedef vector<ll> vll;

typedef vector<ii> vii;

typedef vector<vi> vvi;

template <class T>
T read() {
    T value;
    cin >> value;
    return value;
}

int read_int() {
    return read<int>();
}

size_t read_size() {
    return read<size_t>();
}

ll read_ll() {
    return read<ll>();
}

string read_string() {
    return read<string>();
}

template <class T>
void read_vector(vector<T> & a, size_t size){
    a.resize(size);
    for (T & value : a) cin >> value;
}

void read_pairs(vii & a, size_t size) {
    a.resize(size);
    for (ii & value : a) cin >> value.first >> value.second;
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

vi reverse(vi a) {
    reverse(a.begin(), a.end());
    return a;
}

vector<int> concat_separated(vi & a, vi & b, int sep = -1) {
    size_t n = a.size(), m = b.size();
    vi s(n + 1 + m);
    for (int i = 0; i < n; ++i) s[i] = a[i];
    s[n] = sep;
    for (int j = 0; j < m; ++j) s[n + 1 + j] = b[j];
    return s;
}

const int BASE = 1000'000'000 + 7;
const int MODULO = 1000'000'000 + 31; //998244353

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
    vi parents;
    vi ranks;

    DSU(size_t n = 1) {
        resize(n);
    }

    void resize(size_t n) {
        parents.resize(n);
        for (int v = 0; v < n; ++v) {
            parents[v] = v;
        }

        ranks.resize(n, 1);
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

    bool connected(int f, int t) {
        return get(f) == get(t);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    DSU dsu;
    for (string type; cin >> type; ) {
        if ("RESET" == type) {
            size_t n = read_size();
            dsu.resize(n + 1);

            cout << "RESET DONE" << ENDL;
        } else {
            int from = read_int(), to = read_int();

            if ("JOIN" == type) {
                if (!dsu.merge(from, to)) {
                    cout << "ALREADY" << SPACE << from << SPACE << to << ENDL;
                }
            }

            if ("CHECK" == type) {
                bool answer = dsu.connected(from, to);
                cout << (answer ? "YES" : "NO") << ENDL;
            }
        }
    }

    return 0;
}