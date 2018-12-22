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

int get_bit(ll mask, int bit) {
    return (int)((mask >> bit) & 1);
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

bool contains(const string & p, vector<int> prefix) {
    for (int i = p.size() + 1; i < prefix.size(); ++i) {
        if (prefix[i] == p.size()) {
            return true;
        }
    }

    return false;
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

const int MAX_LENGTH = 2'000'000 + 100;

struct Node {
    int value;
    vector<int> children;
} nodes[MAX_LENGTH];

int size = 0;
int root = ++size;

const int SHIFT = 22;
const int MASK = (1 << SHIFT) - 1;

int find_child(int v, int letter) {
    Node & node = nodes[v];
    for (int i = 0; i < node.children.size(); ++i) {
        int full = node.children[i];
        int child_letter = full >> SHIFT;
        if (child_letter == letter) {
            return full & MASK;
        }
    }

    int id = ++size;
    node.children.push_back((letter << SHIFT) | id);

    return id;
}

void add_word(string & s, ll mask) {
    int v = root;
    for (int i = 0; i < s.size(); ++i) {
        int letter = s[i] - 'a';

        int next = find_child(v, letter);
        if (get_bit(mask, i + 1)) {
            nodes[next].value++;
        }

        v = next;
    }
}

int get_value(string & s) {
    int v = root;
    for (int i = 0; i < s.size(); ++i) {
        int letter = s[i] - 'a';
        v = find_child(v, letter);
    }

    return nodes[v].value;
}

ll calculate_suprefs(string & s) {
    vector<int> z = z_function(s);

    ll mask = (1LL << s.size());

    for (int i = 1; i < s.size(); ++i) {
        if (z[i] + i == s.size()) mask |= (1LL << z[i]);
    }

    return mask;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        ll mask = calculate_suprefs(s);
        add_word(s, mask);
    }

    size_t m;
    cin >> m;

    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;

        int answer = get_value(s);
        cout << answer << ENDL;
    }

    return 0;
}