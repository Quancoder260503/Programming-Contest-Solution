#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN (int)1e6 + 5
#define pii pair<int,int>
#define mp make_pair
#define BASE 63
vector<pii>adj[MAXN]; 
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
        for(int mask = BASE; mask >= 0; mask--)
        {
             if( (ans xor A[mask]) < ans)
             {
                 ans = ans xor A[mask]; 
             }
        }
        return ans;
    }
};
lint dist[MAXN];
linear_basis linb;
bool vis[MAXN]; 
void dfs(int u)
{
    vis[u] = 1; 
    for(int i = 0; i < (int) adj[u].size(); i++)
    {
         int v = adj[u][i].first;
         int w = adj[u][i].second; 
         if(!vis[v])
         {
             dist[v] = dist[u] xor w; 
             dfs(v); 
         }
         else
         {
             linb.add(dist[v] xor dist[u] xor w); 
         }
    }
}
signed main(void)
{
    int n, m;
    scanf("%d %d", &n, &m);
    linb.init();
    for (int i = 0; i < m; i++)
    {
        int u,v,w; scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back(mp(v,w));
        adj[v].push_back(mp(u,w)); 
    }
    dfs(1); 
    printf("%lld\n", linb.findmin(dist[n])); 
    return 0;
}
