#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define mp make_pair
#define pii pair<int,int>
int fa[MAXN], comp[MAXN], deg[MAXN];
set<pii>edge;
int n, m, cycles;
vector<int>tadj[MAXN]; 
int find(int u)
{
     return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
void unite(int u, int v)
{
     int ku = find(u); int kv = find(v);
     if(ku == kv)
     { 
         cycles += (u != v); 
         return;
     }
     if(comp[ku] > comp[kv])
     {
         swap(ku, kv);
     }
     comp[kv] += comp[ku]; 
     fa[ku] = kv; 
     return;
}
signed main(void)
{
     scanf("%d %d", &n, &m);
     for(int i = 1; i <= m; i++)
     {
         comp[i] = 1; 
         fa[i] = i; 
     }
     for(int i = 0; i < n; i++)
     {
         int u,v; scanf("%d %d", &u, &v); 
         if(u > v) swap(u, v); 
         if(u == v)
         {
             deg[v] += 1; 
         }
         else if(!edge.count(mp(u, v)))
         {
             deg[u] += 1;
             deg[v] += 1;
             tadj[u].push_back(v);
             tadj[v].push_back(u);
             edge.insert(mp(u, v));
             unite(u, v);
         }
     }
     int ans = 1; 
     int components = m; 
     for(int i = 1; i <= m; i++)
     {
         int tot = 0; 
         components -= (deg[i] == 0); 
         for(int j = 0; j < tadj[i].size(); j++)
         {
             int v = tadj[i][j]; 
             tot += (deg[v] >= 2);
         }
         ans = ans & (tot <= 2); 
     }
     if(ans == 0)
     {
        puts("impossible"); 
        return 0; 
     }
     // if there is a cycle in the graph --> there must be only 1 components
    //  if there is more than one cycle --> impossible
     for(int i = 1; i <= m; i++)
     {
         if(fa[i] == i && deg[i] > 0)
         {
            components +=  1 - comp[i]; 
         }
     }
     if(cycles == 0)
     {
         puts("possible");
         return 0; 
     }
     if(cycles == 1 && components == 1)
     {
         puts("possible"); 
     }
     else
     {
        puts("impossible"); 
     }
     return 0; 
}