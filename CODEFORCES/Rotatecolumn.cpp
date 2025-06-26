#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e3 + 10
int n, m;
int arr[MAXN][MAXN];
void solve()
{
    cin >> n >> m;
    vector<int> cm(m, 0);
    vector<int> ord(m, 0);
    memset(arr, 0, sizeof(arr));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
            cm[j] = max(cm[j], arr[i][j]);
        }
    }
    vector<vector<int>> dp(2, vector<int>(1 << n, 0));
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j)
         { return cm[i] > cm[j]; });
    if (ord.size() > n)
    {
        ord.resize(n);
    }
    for (int i = 0; i < (int)ord.size(); i++)
    {
        int pos = ord[i];
        vector<int> opt(1 << n, 0);
        for (int k = 0; k < n; k++)
        {
            for (int mask = 0; mask < (1 << n); mask++)
            {
                int tot = 0;
                int fmask = 0;
                for (int j = 0; j < n; j++)
                {
                    if (mask & (1 << j))
                    {
                        fmask |= 1 << ((k + j) % n);
                        tot += arr[j][pos];
                    }
                }
                opt[fmask] = max(opt[fmask], tot);
            }
        }
        for (int mask = 0; mask < (1 << n); mask++)
        {
            for (int fmask = mask; fmask < (1 << n); fmask = mask | (fmask + 1))
            {
                dp[1][fmask] = max(dp[1][fmask], dp[0][mask xor fmask] + opt[mask]);
            }
        }
        for (int mask = 0; mask < (1 << n); mask++)
        {
            dp[0][mask] = dp[1][mask];
            dp[1][mask] = 0;
        }
    }
    cout << dp[0][(1 << n) - 1] << '\n';
}
signed main(void)
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
    return 0;
}