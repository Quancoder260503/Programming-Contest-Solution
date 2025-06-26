#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 2e5 + 10
#define mp make_pair 
#define lint long long
#define pii pair<int,int> 
vector<pii>adj[MAXN]; 
int arr[MAXN]; 
int dep[MAXN];
int dp[MAXN]; 
lint ans[MAXN]; 
int trs[MAXN]; 
lint totd, totv, totc, n;
void dfs(int u, int p)
{
     dp[u] += arr[u]; 
     trs[u] += 1;
     for(int i = 0; i < adj[u].size(); i++)
     {
         int v = adj[u][i].first;
         if(v == p) continue;
         dep[v] = dep[u] + adj[u][i].second; 
         dfs(v, u);
         dp[u] += dp[v]; 
         trs[u] += trs[v]; 
     }
}
/* */ 
void dfs2(int u, int p, int w, lint tdist, lint tval)
{
     if(p)
     {
         tdist += (n - 2 * trs[u]) * w;
         tval += 1LL * (dp[1] - 2 * dp[u]) * w;
         ans[u] = 1LL * tdist * arr[u] + tval;
     }
     for(int i = 0; i < adj[u].size(); i++)
     {
          int v = adj[u][i].first;
          if(v == p) continue; 
          dfs2(v, u, adj[u][i].second, tdist, tval); 
     }
     return;
}
signed main(void)
{
    cin >> n; 
    for(int i = 1; i <= n; i++)
    {
       cin >> arr[i];     
    }
    for(int i = 1; i < n; i++)
    {
       int u, v, w; cin >> u >> v >> w;
       adj[u].push_back(mp(v, w));
       adj[v].push_back(mp(u, w));     
    }
    dfs(1, 0); 
    for(int i = 1; i <= n; i++)
    {
         totd += dep[i]; 
         totv += 1LL * dep[i] * arr[i];  
    }
    ans[1] = totv + 1LL * totd * arr[1];
    dfs2(1, 0, 0, totd, totv);
    for(int i = 1; i <= n; i++)
    {
         cout << ans[i] << '\n'; 
    } 
    return 0; 
}