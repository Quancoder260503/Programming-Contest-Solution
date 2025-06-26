#include "bits/stdc++.h"
using namespace std;
const int N = 1e5 + 1;
const int M = 101;
int n, k; 
long long dp[N][M][2];
int A[N]; 
vector<int>adj[N]; 
int trs[N];
vector<int>topo;
void dfs(int u, int p)
{
    topo.push_back(u); 
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p)
            continue;
        dfs(v, u);
        trs[u] += trs[v];
    }
    return;
}
void solve()
{
    scanf("%d %d", &n, &k);
    int curr = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &A[i]);
        curr = max(curr, A[i]); 
    }
    if(curr <= 0)
    {
        printf("%d\n", curr);
        return; 
    }
    memset(dp, 0, sizeof(dp)); 
    topo.resize(0); 
    for (int i = 1; i <= n; i++)
    {
        adj[i].resize(0); 
        trs[i] = 1;
    }
    for (int i = 2; i <= n; i++)
    {
        int u;
        scanf("%d", &u);
        adj[++u].push_back(i);
    } 
    dfs(1, 0); 
    long long ans = 0;
    reverse(topo.begin(), topo.end()); 
    for(int k = 0; k < topo.size(); k++)
    {
        int u = topo[k]; 
        dp[u][1][1] = max(dp[u][1][1], 1LL * A[u]);
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            for (int j = min(k, trs[u]); j >= 0; j--)
            {
                for (int p = 0; p <= j; p++)
                {
                    dp[u][j][0] = max(dp[u][j][0], dp[u][p][0] + dp[v][j - p][1]);
                    dp[u][j][1] = max(dp[u][j][1], dp[u][p][1] + dp[v][j - p][0]);
                    dp[u][j][1] = max(dp[u][j][1], dp[u][p][0] + dp[v][j - p][1]);
                }
            }
        }
    }
    for(int i = 1; i <= k; i++)
    {
       ans = max(ans, dp[1][i][1]); 
    }
    printf("%d\n", ans); 
    return;
}
signed main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}