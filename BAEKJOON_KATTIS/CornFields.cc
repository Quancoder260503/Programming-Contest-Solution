#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int mod = 1e8;
signed main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<lint>> g(n, vector<lint>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
        }
    }
    vector<int> row(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (g[i][j]) row[i] |= (1 << j);
        }
    }
    auto chk = [&](int mask)
    {
        for (int i = 0; i + 1 < m; i++)
        {
            if (mask & (1 << i) && mask & (1 << (i + 1)))
                return 0;
        }
        return 1;
    };
    vector<int> state((1 << m));
    for (int mask = 0; mask < (1 << m); mask++)
    {
        state[mask] = chk(mask);
    }
    vector<vector<int>> dyn(n, vector<int>((1 << m), 0));
    for (int i = 0; i < n; i++)
    {
        for (int mask = 0; mask < (1 << m); mask++)
        {
            if ((mask & row[i]) == mask && state[mask])
            {
                if (i == 0)
                {
                    dyn[i][mask]++;
                }
                else
                {
                    int rmask = ((1 << m) - 1) xor mask;
                    for (int fmask = rmask; fmask; fmask = (fmask - 1) & rmask)
                    {
                        dyn[i][mask] = (dyn[i][mask] + dyn[i - 1][fmask] + mod) % mod;
                    }
                    dyn[i][mask] += dyn[i - 1][0]; 
                }
            }
        }
    }
    lint ans = 0;
    for (int mask = 0; mask < (1 << m); mask++)
    {
        if(state[mask]) ans = (ans + dyn[n - 1][mask] + mod) % mod; 
    }
    cout << ans << '\n'; 
    return 0;
}