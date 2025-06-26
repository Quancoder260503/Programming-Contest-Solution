#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    // J4F problems
    auto solve = [&](int n, int m, vector<vector<int>> vis)
    {
        vector<vector<int>> dyn(n, vector<int>(m, 0));
        dyn[0][0] = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if(vis[i][j] || (i == 0 && j == 0)) continue;
                dyn[i][j] = (i ? dyn[i - 1][j] : 0) + (j ? dyn[i][j - 1] : 0);
            }
        }
        return dyn[n - 1][m - 1]; 
    };
    int n, m; 
    int prob = 0; 
    while(cin >> n >> m)
    {
        if(n == 0 && m == 0) break; 
        int u, v; 
        prob++;
        vector<vector<int>>vis(n, vector<int>(m, 0)); 
        while(cin >> u >> v)
        {
            if(u == 0 && v == 0) break; 
            vis[u][v] = 1; 
        }
        printf("Map %d: %d\n", prob, solve(n, m, vis));
    }
    return 0;
}