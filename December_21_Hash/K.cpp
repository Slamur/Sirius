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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    const int SIZE = 6'000'000;
    vector<pair<int, int>> fibs(SIZE);
    fibs[0] = { 1, 1 };
    fibs[1] = { 1, 1 };

    const int MODULO_1 = 1'000'000'007, MODULO_2 = 1'000'000'031;

    for (int i = 2; i < SIZE; ++i) {
        fibs[i].first = add<MODULO_1>(fibs[i - 1].first, fibs[i - 2].first);
        fibs[i].second = add<MODULO_2>(fibs[i - 1].second, fibs[i - 2].second);
    }

    sort(fibs.begin(), fibs.end());

    int n;
    cin >> n;

    while (n --> 0) {
        string s;
        cin >> s;

        pair<int, int> hash(0, 0);
        for (char ch : s) {
            int digit = ch - '0';

            hash.first = multiply<MODULO_1>(hash.first, 10);
            hash.first = add<MODULO_1>(hash.first, digit);

            hash.second = multiply<MODULO_2>(hash.second, 10);
            hash.second = add<MODULO_2>(hash.second, digit);
        }

        bool answer = binary_search(fibs.begin(), fibs.end(), hash);
        cout << (answer ? "Yes" : "No") << ENDL;
    }

    return 0;
}