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

vector<int> NOT_ANSWER(0);

int get_bit(int mask, int bit) {
    return (mask >> bit) & 1;
}

vector<int> generate(vector<int> & p, int alphabet) {
    size_t n = p.size();
    for (int i = 0; i < n; ++i) {
        int prev = (i == 0 ? -1 : p[i - 1]);
        if (p[i] > prev + 1) return NOT_ANSWER;
    }

    vector<int> s(n);

    s[0] = 0;
    for (int i = 1; i < n; ++i) {
        if (p[i] > 0) {
            s[i] = s[p[i] - 1];
        } else {
            int mask = 1;
            for (int j = i - 1; j > 0; ) {
                mask |= (1 << s[p[j]]);
                j = p[j] - 1;
            }

            bool found = false;
            for (int ch = 0; ch < alphabet && !found; ++ch) {
                if (!get_bit(mask, ch)) {
                    s[i] = ch;
                    found = true;
                }
            }

            if (!found) {
                return NOT_ANSWER;
            }
        }
    }

    return s;
}

vector<int> prefix_function(vector<int> & s) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    for (size_t n; cin >> n; ) {
        int alphabet;
        cin >> alphabet;

        vector<int> p(n);
        for (int i = 0; i < n; ++i) cin >> p[i];

        vector<int> s = generate(p, alphabet);

        bool correct = (s != NOT_ANSWER && p == prefix_function(s));
        if (correct) {
            cout << "YES" << '\n';
            for (int ch : s) {
                cout << (char)(ch + 'a');
            }
            cout << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }

    return 0;
}