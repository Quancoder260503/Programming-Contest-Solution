#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)1001;
int table[MAXN][MAXN];
char g[MAXN][MAXN];
int n, m, W, H;
bool get_rec(int r1, int c1, int r2, int c2)
{
    return (table[r2][c2] + table[r1 - 1][c1 - 1]  ==  table[r1 - 1][c2] + table[r2][c1 - 1]);
}
signed main(void)
{
    cin >> n >> m >> W >> H;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            char ch;
            cin >> ch;
            table[i][j] = (ch == 'A');
            table[i][j] += table[i][j - 1] + table[i - 1][j] - table[i - 1][j - 1];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {

            if (i + W - 1 <= n && j + H - 1 <= m)
                ans += get_rec(i, j, i + W - 1, j + H - 1);
            if (H != W && i + H - 1 <= n && j + W - 1<= m)
                ans += get_rec(i, j, i + H - 1, j + W - 1);
        }
    }
    cout << ans << endl;
}