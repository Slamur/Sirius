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

string get_period(string & s) {
    size_t n = s.size();

    vector<int> prefix = prefix_function(s);
    vector<int> z = z_function(s);

    for (size_t i = 1; i < n; ++i) {
        int tail = n % i;

        int head = n - tail;
        if (prefix[n - 1] + i != n) {
            continue;
        }

        if (tail > 0) {
            if (z[head] != tail) continue;
        }

        return s.substr(0, i);
    }

    return s;
}

bool contains(const string & p, vector<int> prefix) {
    for (int i = p.size() + 1; i < prefix.size(); ++i) {
        if (prefix[i] == p.size()) {
            return true;
        }
    }

    return false;
}

bool correct(string & period, string & a, string & b) {
    size_t n = a.size(), m = b.size();

    string full = "";
    while (full.size() < n + m + n + m) {
        full += period;
    }

    {
        auto af = concat_separated(a, full);
        if (!contains(a, prefix_function(af))) {
            return false;
        }
    }

    {
        auto bf = concat_separated(b, full);
        if (!contains(b, prefix_function(bf))) {
            return false;
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string a, b;
    cin >> a >> b;

    vector<string> fulls = {a + b, b + a};

    {
        auto ab = concat_separated(a, b);
        auto ab_prefix = prefix_function(ab);

        if (contains(a, ab_prefix)) {
            fulls.push_back(b);
        }

        size_t last_prefix = (size_t) ab_prefix[ab.size() - 1];
        fulls.push_back(b + a.substr(last_prefix));
    }

    {
        auto ba = concat_separated(b, a);
        auto ba_prefix = prefix_function(ba);

        if (contains(b, ba_prefix)) {
            fulls.push_back(a);
        }

        size_t last_prefix = (size_t) ba_prefix[ba.size() - 1];
        fulls.push_back(a + b.substr(last_prefix));
    }

    string answer = a + b;

    for (string &full : fulls) {
        string period = get_period(full);

        if (answer.size() > period.size()) {
            answer = period;
        }
    }

    cout << answer << ENDL;
    return 0;
}