#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long ll;

void read_ints(size_t size, vector<int> & a){
    a.resize(size);
    for (int & value : a) cin >> value;
}

void print_ints(vector<int> & a, char sep = ' ') {
    for (int value : a) cout << value << sep;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n;
    cin >> n;

    string s;
    cin >> s;

    vector<int> a(n + 1 + n);
    for (int i = 0; i < n; ++i) {
        a[i] = s[i];
    }
    a[n] = -1;
    for (int i = n + 1, j = n - 1; i < a.size(); ++i, --j) {
        a[i] = s[j];
    }

    vector<int> z = z_function(a);

    vector<int> answers(n, 0);
    for (int i = n + 1, j = n - 1; i < a.size(); ++i, --j) {
        answers[j] = z[i];
    }
    print_ints(answers);

    return 0;
}