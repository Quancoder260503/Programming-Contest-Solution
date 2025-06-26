#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10
#define pii pair<int,int> 
#define mp make_pair
int n;
int dp[MAXN][2]; 
int ans[MAXN];
vector<int> adj[MAXN];
void dfs(int u, int p)
{
    for(int i = 0; i < adj[u].size(); i++)
    {
         int v = adj[u][i];
         if(v == p) continue; 
         dfs(v, u);
         if(dp[v][0] + 1 > dp[u][0])
         {
             dp[u][1] = dp[u][0];
             dp[u][0] = dp[v][0] + 1; 
         }
         else if (dp[v][0] + 1 > dp[u][1])
         {
             dp[u][1] = dp[v][0] + 1; 
         }
    }
    return; 
}
void dfs2(int u, int p, int w = 0)
{ 
    ans[u] = max(dp[u][0], w); 
    for(int i = 0; i < adj[u].size(); i++)
    {
         int v = adj[u][i];
         if(v == p) continue;
         if(dp[u][0] == dp[v][0] + 1)
         {
            dfs2(v, u, max(dp[u][1], w) + 1);
         }
         else 
         {
             dfs2(v, u, ans[u] + 1); 
         } 
    }
    return; 
}
void solve()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
    { 
         adj[i].clear(); 
         dp[i][0] = dp[i][1] = ans[i] = 0;
    }
    for(int i = 0; i < n - 1; i++)
    {
         int u, v; 
         cin >> u >> v;
         ++u; ++v;
         adj[u].push_back(v);
         adj[v].push_back(u); 
    }
    dfs(1, 0); 
    dfs2(1, 0);
    int res = MAXN;  
    for(int i = 1; i <= n; i++)
    {
         res = min(res, ans[i]); 
    }
    cout << res << '\n';
    return;
}
signed main(void)
{ 
    int t; 
    cin >> t; 
    while(t--)
    {
        solve(); 
    }
    return 0; 
}
/*
  LET F[i] = {furthest node from node i on the tree}
  -> ans = min(F[i])
*/