#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long ll;

int gcd(int a, int b) {
    return (a == 0 ? b : gcd(b % a, a));
}

class SparseTable {

public:

    const int MAX_BIT = 19; // 100k <= (1 << 19)

    int size;
    vector<vector<int>> table;
    vector<int> max_bits;

    SparseTable(int n)
            : size(n)
            , table(MAX_BIT, vector<int>(size, 0))
            , max_bits(size + 1, 0)
    {
        max_bits[1] = 0;
        for (int len = 2; len <= size; ++len) {
            max_bits[len] = max_bits[len / 2] + 1;
        }
    }

    void build(vector<int> & a) {
        for (int i = 0; i < size; ++i) {
            table[0][i] = a[i];
        }

        for (int bit = 0; bit < MAX_BIT - 1; ++bit) {
            int half = (1 << bit);
            for (int i = 0, j = half; j + half <= size; ++i, ++j) {
                table[bit + 1][i] = gcd(table[bit][i], table[bit][j]);
            }
        }
    }

    int get(int start, int end) {
        ++end;
        int length = end - start;

        int bit = max_bits[length];
        int power = (1 << bit);

        int result = gcd(
            table[bit][start],
            table[bit][end - power]
        );

        return result;
    }
};

int main(){
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    SparseTable table(n);
    table.build(a);

    int m;
    cin >> m;

    while (m --> 0) {
        int start, end;
        cin >> start >> end;

        --start, --end;

        int answer = table.get(start, end);
        cout << answer << ' ';
    }

    cout << endl;

    return 0;
}