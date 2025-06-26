#include "bits/stdc++.h"
using namespace std;
#define MAXN 3000
#define lint long long
int n; 
vector<int>adj[MAXN]; 
vector<int>radj[MAXN]; 
vector<int>topo;
bool vis[MAXN]; 
vector<int>comp[MAXN];
void dfs(int u)
{
     vis[u] = 1;
     for(int i = 0; i < adj[u].size(); i++)
     {
         int v = adj[u][i];
         if(vis[v]) continue; 
         dfs(v); 
     }
     topo.push_back(u);
}
void dfs2(int u, int curr)
{
     vis[u] = 1; 
     comp[curr].push_back(u);
     for (int i = 0; i < radj[u].size(); i++)
     {
         int v = radj[u][i];
         if (vis[v]) continue;
         dfs2(v, curr);
     }
}
signed main(void)
{
     scanf("%d", &n);
     int m = 0;
     for(int i = 0; i < n; i++)
     {
         for(int j = 0; j < n; j++)
         {
             int x; scanf("%d", &x);
             if(x)
             {
                 adj[i].push_back(j); 
                 radj[j].push_back(i); 
                 m++; 
             } 
         }
     }
     for(int i = 0; i < n; i++)
     {
         if(!vis[i])
         {
             dfs(i); 
         }
     }
     memset(vis, 0, sizeof(vis)); 
     reverse(topo.begin(), topo.end()); 
     int sz = 0;
     for(int i = 0; i < topo.size(); i++)
     {
         int u = topo[i];
         if(!vis[u])
         {
             dfs2(u, sz);
             sz += 1;  
         }
     }
     lint ans = -m; 
     for(int i = 0; i < sz; i++)
     { 
         ans += 1LL * comp[i].size() * (comp[i].size() - 1); 
         for(int j = i + 1; j < sz; j++)
         {
             ans += 1LL * comp[i].size() * comp[j].size(); 
         }
     }
     printf("%lld\n", ans);
     return 0;
}