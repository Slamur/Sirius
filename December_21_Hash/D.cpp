#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
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


template <int base, int modulo>
struct HashRight {

    vector<int> base_powers;

    void init_hash(size_t size)
    {
        ++size;
        base_powers.resize(size, 0);
        base_powers[0] = 1;
        for (int i = 1; i < size; ++i) {
            base_powers[i] = multiply<modulo>(base_powers[i - 1], base);
        }
    }

    vector<int> calculate_hashes(string & s) {
        int size = s.size();
        vector<int> hashes(size + 1, 0);

        for (int i = 0; i < size; ++i) {
            hashes[i + 1] = add<modulo>(
                    multiply<modulo>(hashes[i], BASE),
                    s[i]
            );
        }

        return hashes;
    }

    int calculate_hash(string & s) {
        return calculate_hashes(s)[s.size()];
    }

    // [start..end)
    int get_hash(vector<int> & hashes, int start, int end) {
        return subtract<modulo>(
                hashes[end],
                multiply<modulo>(hashes[start], base_powers[end - start])
        );
    }

    int calculate_period(string & s) {
        size_t n = s.size();
        init_hash(n);

        vector<char> is_periods(n + 1, false);

        auto s_hashes = calculate_hashes(s);

        for (int i = 1; i <= n; ++i) {
            int period_hash = s_hashes[i];

            int tail = n % i;
            int head = n - tail;

            int head_hash = s_hashes[head];
            int tail_hash = get_hash(s_hashes, head, n);

            int full_period_hash = multiply<modulo>(period_hash,
                                               subtract<modulo>(base_powers[head], 1)
            );

            int full_head_hash = multiply<modulo>(head_hash,
                                               subtract<modulo>(base_powers[i], 1)
            );

            if (full_period_hash == full_head_hash
                &&
                s_hashes[tail] == tail_hash) {
                return i;
            }
        }

        return n;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;

    HashRight<BASE, MODULO> hash;

    int answer = hash.calculate_period(s);
    cout << answer << endl;

    return 0;
}