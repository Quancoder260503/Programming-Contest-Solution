#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int mod = 1e9 + 7;
signed main(void)
{
    int K, n, m;
    cin >> K >> n >> m;
    vector<vector<lint>> dyn(n + 1, vector<lint>(K + 1, 0));
    for (int i = 0; i <= min(m, K); i++)
    {
        dyn[1][i]++;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= K; j++)
        {
            for (int jj = 0; jj <= min(m, j); jj++)
            {
                dyn[i][j] = (dyn[i][j] + dyn[i - 1][j - jj] + mod) % mod;
            }
        }
    }
    lint ans = 0;
    for (int i = 0; i <= K; i++)
    {
        ans = (ans + dyn[n][i] + mod) % mod;
    }
    for (int i = 0; i <= m; i++)
    {
        if (n * i <= K)
        {
            ans = (ans - 1 + mod) % mod;
        }
    }
    cout << ans << '\n';
    return 0;
}