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

const int BASE = 1000'000'000 + 7;
const int MODULO = 1000'000'000 + 31;

inline int add(int a, int b) {
    return (a + b) % MODULO;
}

inline int subtract(int a, int b) {
    return add(a, MODULO - b);
}

inline int multiply(ll a, ll b) {
    return (int)((a * b) % MODULO);
}

struct HashLeft {

    vector<int> base_powers;

    void init_hash(size_t size)
    {
        base_powers.resize(size, 0);
        base_powers[0] = 1;
        for (int i = 1; i < size; ++i) {
            base_powers[i] = multiply(base_powers[i - 1], BASE);
        }
    }

    vector<int> calculate_hashes(string & s) {
        int size = s.size();
        vector<int> hashes(size + 1, 0);

        for (int i = 0; i < size; ++i) {
            hashes[i + 1] = add(
                    hashes[i],
                    multiply(s[i], base_powers[i])
            );
        }

        return hashes;
    }

    int calculate_hash(string & s) {
        return calculate_hashes(s)[s.size()];
    }

    // [start..end)
    int get_hash(vector<int> & hashes, int start, int end) {
        return subtract(hashes[end], hashes[start]);
    }

    vector<int> find(string & s, string & t) {
        size_t size = max(s.size(), t.size()) + 1;
        init_hash(size);

        vector<int> s_hashes = calculate_hashes(s);

        int t_hash = calculate_hash(t);
        int t_size = t.size();

        vector<int> positions;

        for (int i = 0; i + t_size <= s.size(); ++i) {
            int s_hash = get_hash(s_hashes, i, i + t_size);
            if (multiply(t_hash, base_powers[i]) == s_hash) {
                positions.push_back(i);
            }
        }

        return positions;
    }
};

struct HashRight {

    vector<int> base_powers;

    void init_hash(size_t size)
    {
        base_powers.resize(size, 0);
        base_powers[0] = 1;
        for (int i = 1; i < size; ++i) {
            base_powers[i] = multiply(base_powers[i - 1], BASE);
        }
    }

    vector<int> calculate_hashes(string & s) {
        int size = s.size();
        vector<int> hashes(size + 1, 0);

        for (int i = 0; i < size; ++i) {
            hashes[i + 1] = add(
                    multiply(hashes[i], BASE),
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
        return subtract(
                hashes[end],
                multiply(hashes[start], base_powers[end - start])
        );
    }

    vector<int> find(string & s, string & t) {
        size_t size = max(s.size(), t.size()) + 1;
        init_hash(size);

        vector<int> s_hashes = calculate_hashes(s);

        int t_hash = calculate_hash(t);
        int t_size = t.size();

        vector<int> positions;

        for (int i = 0; i + t_size <= s.size(); ++i) {
            int s_hash = get_hash(s_hashes, i, i + t_size);
            if (t_hash == s_hash){
                positions.push_back(i);
            }
        }

        return positions;
    }
};

int main() {
    string s;
    cin >> s;

    string t;
    cin >> t;

//    HashLeft hash;
    HashRight hash;

    vector<int> positions = hash.find(s, t);
    for (int position : positions) {
        cout << position << " ";
    }
    cout << endl;

    return 0;
}