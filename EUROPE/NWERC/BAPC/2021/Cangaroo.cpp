#include "bits/stdc++.h"
using namespace std;
const int INF = 1e9;
signed main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int> smask;
    for (int mask = 0; mask < (1 << (m - 1)); mask++)
    {
        if (mask & (mask << 1))
            continue;
        smask.push_back(mask);
    }
    vector<vector<char>> g(n, vector<char>(m));
    vector<int> row(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
        }
    }
    for (int i = 0; i < n; i += 2)
    {
        for (int j = 0; j < m; j++)
        {
            if(g[i][j] == '#') row[i] |= (1 << j); 
            if(g[i + 1][j] == '#') row[i] |= (1 << j); 
        }
    }
    vector<vector<int>> dyn(n, vector<int>((1 << m), INF));
    for (int i = 0; i < n; i += 2)
    {
        for (int mask = 0; mask < (1 << m); mask++)
        {
            int ss = mask | (mask >> 1) | (mask << 1);
            for (auto fmask : smask)
            {
                if (~ss & fmask) continue;
                if (row[i] & ~(fmask | (fmask << 1))) continue;
                dyn[i][mask] = min((i > 1 ? dyn[i - 2][fmask] : 0) + __builtin_popcount(fmask), dyn[i][mask]);
            }
        }
    }
    cout << dyn[n - 2][(1 << m) - 1] << '\n'; 
    return 0;
}