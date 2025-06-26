#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define lint long long 
vector<int>adj[MAXN]; 
int n; 
int trs[MAXN];
bitset<MAXN> dp;
int arr[MAXN]; 
int dfs(int u, int p)
{
    trs[u] = 1; 
    for(int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if(v == p) continue; 
        trs[u] += dfs(v, u); 
    }
    return trs[u]; 
}
int centroid(int u, int p, int sz)
{
     for(int i = 0; i < adj[u].size(); i++)
     {
         int v = adj[u][i];
         if(v == p) continue;
         if(trs[v] * 2 >=  sz) 
         {
             return centroid(v, u, sz); 
         }
     }
     return u;
}
signed main(void)
{
     scanf("%d", &n);
     for(int i = 2; i <= n; i++)
     {
         int u; scanf("%d", &u);
         adj[u].push_back(i); 
         adj[i].push_back(u); 
     }
     dfs(1, 0); 
     int c = centroid(1, 0, n);
     memset(trs, 0, sizeof(trs)); 
     dfs(c, 0);   
     dp[0] = 1; 
     for(int i = 0; i < adj[c].size(); i++)
     {
         int v = adj[c][i]; 
         arr[trs[v]] += 1; 
     }
     for(int i = 0; i < n; i++)
     {
         if(arr[i] > 0)
         {
             for(lint j = 1; j <= arr[i]; j = j * 2)
             {
                 dp |= (dp << (1LL * j * i)); 
                 arr[i] -= j; 
             }
             if(arr[i] > 0)
             {
                 dp |= (dp << (arr[i])); 
             }
         }
     }
     lint ans = 0;
     for(int i = 0; i < n; i++)
     {
         if(dp[i])
         {
             ans = max(ans, 1LL * i * (n - i - 1)); 
         }
     }
     for(int i = 1; i <= n; i++)
     {
         ans += trs[i]; 
     }
     printf("%lld \n", ans); 
     return 0; 
}
/*
   It is not difficult to see that when we using the centroid as the main crossroad -> there will be more pleasing tour
   The next step is to compute the number of pleasing tour 
   -> let S be the number of nodes to the centroid whose path is increasing 
      let T be the number of nodes to the centroid whose path is decreasing 
      T + S = n - 1 
      Thus the number of pleasing tour is (T * S) = (T ) * (n - T - 1)
      --> we have to maximise this value 
*/ 