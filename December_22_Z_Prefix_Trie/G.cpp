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

vector<int> NOT_ANSWER(0);

int get_bit(int mask, int bit) {
    return (mask >> bit) & 1;
}

template <class T>
vector<int> prefix_function(T & s) {
    size_t n = s.size();
    if (n == 0) return NOT_ANSWER;

    vector<int> prefix(n);

    prefix[0] = 0;
    for (int i = 1; i < n; ++i) {
        int j = prefix[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = prefix[j - 1];
        }

        if (s[i] == s[j]) {
            ++j;
        }

        prefix[i] = j;
    }

    return prefix;
}

template <class T>
vector<int> z_function(T & s) {
    size_t n = s.size();
    if (n == 0) return vector<int>(0);

    vector<int> z(n);
    z[0] = 0;

    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (r < i) {
            l = i;
            r = i;
        }

        z[i] = min(z[i - l], r - i);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];

        if (r < i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }

    return z;
}

vector<int> concat_separated(string & a, string & b, int sep = -1) {
    size_t n = a.size(), m = b.size();

    vector<int> s(n + 1 + m);
    for (int i = 0; i < n; ++i) s[i] = a[i];
    s[n] = sep;
    for (int j = 0; j < m; ++j) s[n + 1 + j] = b[j];

    return s;
}

int count_periods(string & s) {
    size_t n = s.size();

    vector<int> prefix = prefix_function(s);
    vector<int> z = z_function(s);

    vector<int> used(n + 1, 0);
    used[n] = 1;

    for (size_t i = 1; i < n; ++i) {
        int tail = n % i;

        int head = n - tail;
        if (prefix[n - 1] + i != n) {
            continue;
        }

        if (tail > 0) {
            continue;
//            if (z[head] != tail) continue;
        }

        for (int len = i; len <= n; len += i) used[len] = 1;
    }

    int result = 0;
    for (int value : used) result += value;

    return result;
}

bool contains(const string & p, vector<int> prefix) {
    for (int i = p.size() + 1; i < prefix.size(); ++i) {
        if (prefix[i] == p.size()) {
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s;
    cin >> s;

    reverse(s.begin(), s.end());

    int answer = count_periods(s);
    cout << answer << endl;

    return 0;
}