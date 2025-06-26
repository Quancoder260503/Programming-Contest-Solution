#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int M = 8;
const int MAXN = (int) 20000;
lint dp[M][M][MAXN];
int g[M][M];
int cur[65];
int n, m;
int fmask = 1;
const int mod = 998244353;
lint f(int r, int c, int mask, int at)
{
    if (c == m)
    {
        c = 0, r++;
    }
    if (r == n) return 1;
    if (dp[r][c][mask] != -1) return dp[r][c][mask];
    lint ans = 0;
    for (cur[at] = 0; cur[at] < 3; cur[at]++)
    {
        if (g[r][c] != -1 && g[r][c] != cur[at]) continue;
        if (r > 0 && c > 0 && cur[at - m - 1] == 1 && cur[at - m] == 0 && cur[at] == 0 && cur[at - 1] == 2) continue;
        ans = (ans + f(r, c + 1, (3 * mask + cur[at]) % fmask, at + 1) + mod) % mod;
    }
    return dp[r][c][mask] = ans;
}
signed main(void)
{
    cin >> n >> m;
    char ch;
    for(int i = 0; i <= m; i++) fmask = fmask * 3; 
    memset(g, -1, sizeof(g));
    memset(dp, -1, sizeof(dp));
    lint ans = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> ch;
            ans = ans % mod * (ch == '?' ? 3 : 1) % mod;
            if (ch == '?') continue;
            g[i][j] = (ch == 'C' ? 0 : (ch == 'I' ? 1 : 2));
        }
    }
    cout << (ans - f(0, 0, 0, 0) + mod) % mod << '\n'; 
    return 0; 
}