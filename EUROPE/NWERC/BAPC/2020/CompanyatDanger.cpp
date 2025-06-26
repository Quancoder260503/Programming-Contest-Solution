#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN (int) 1e6 + 5
#define BASE 63
#define pii pair<int,lint>
#define mp make_pair
int n, m, q;
vector<pii> adj[MAXN];
lint dist[MAXN];
bool vis[MAXN];
struct linear_basis
{
    lint A[BASE + 1], B[BASE + 1];
    lint count;
    bool flag;
    void init()
    {
        memset(A, 0, sizeof(A));
        memset(B, 0, sizeof(B));
        count = 0;
        flag = false;
    }
    void add(lint val)
    {
        for (int mask = BASE; mask >= 0; mask--)
        {
            if (val & (1LL << mask))
            {
                if (A[mask])
                {
                    val = val xor A[mask];
                }
                else
                {
                    A[mask] = val;
                    return;
                }
            }
        }
        flag = true;
    }
    lint findmax()
    {
        lint ans = 0;
        for (int mask = BASE; mask >= 0; mask--)
        {
            ans = max(ans, ans xor A[mask]);
        }
        return ans;
    }
    lint findmin(lint val)
    {
        lint ans = val;
        for (int mask = BASE; mask >= 0; mask--)
        {
            ans = min(ans, ans xor A[mask]); 
        }
        return ans;
    }
} linb;
void dfs(int u)
{
     vis[u] = 1; 
     for(int i = 0; i < adj[u].size(); i++)
     {
         int v = adj[u][i].first; 
         lint w = adj[u][i].second; 
         if(!vis[v])
         {
             dist[v] = dist[u] xor w; 
             dfs(v); 
         }
         else
         {
             linb.add(dist[u] xor w xor dist[v]); 
         }
     }
     return; 
}
signed main(void)
{  
     scanf("%d %d %d", &n, &m, &q);
     for(int i = 0; i < m; i++)
     {
         int u,v; lint w ; 
         scanf("%d %d %lld", &u, &v, &w);
         adj[u].push_back(mp(v, w));
         adj[v].push_back(mp(u, w)); 
     }
     dfs(1);
     for(int i = 1; i <= n; i++)
     {
         dist[i] = linb.findmin(dist[i]); 
     }
     for(int i = 0; i < q; i++)
     {
         int u,v; scanf("%d %d", &u, &v);
         lint ans = dist[u] xor dist[v];
         printf("%lld\n", ans); 
     }
     return 0; 
}