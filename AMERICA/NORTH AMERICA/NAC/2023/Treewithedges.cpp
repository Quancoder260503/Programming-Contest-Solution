#include "bits/stdc++.h"
#include <array>
using namespace std; 
#define MAXN (int) 1e6 + 10
#define EXT 2
#define pii pair<int,int>
#define LOG 21
#define mp make_pair
int n, q;
int fa[MAXN];
int up[LOG][MAXN]; 
vector<int>adj[MAXN]; 
array<int,2>edges[2];
int dep[MAXN]; 
int arr[MAXN]; 
int in[MAXN]; 
int out[MAXN];
int timer = 1;  
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
void dfs(int u, int p)
{ 
     in[u] = timer++; 
     for(int i = 1; i < LOG; i++)
     {
         up[i][u] = up[i - 1][up[i - 1][u]]; 
     }
     for(int i = 0; i < adj[u].size(); i++)
     {
         int v = adj[u][i];
         if(v == p) continue;
         dep[v] = dep[up[0][v] = u] + 1; 
         dfs(v, u); 
     }
     out[u] = timer - 1;
     return;
}
int LCA(int u, int v)
{
    if(dep[u] < dep[v]) swap(u, v);
    int dist = dep[u] - dep[v];
    for(int i = 0; i < LOG; i++)
    {
         if(dist & (1 << i)) u = up[i][u]; 
    }
    if(u == v) return u; 
    for(int i = LOG - 1; i >= 0; i--)
    {
         int tu = up[i][u]; int tv = up[i][v];
         if(tu != tv)
         {
             u = tu;
             v = tv; 
         }
    }
    return up[0][u]; 
} 
bool intersect(int u, int v, int p, int q)
{ 
     /*
       check if path from u -> v is intersected with path from p -> q
       and path from p -> q lies within path u -> v
     */ 
     array<int,2>seta = {LCA(u, v), p}; 
     array<int,2>setb = {LCA(u, p), LCA(v, p)}; 
     if(seta == setb) return 1; 
     swap(setb[0], setb[1]);
     if(seta == setb) return 1;
     array<int, 2> setc = {LCA(u, v), q};
     array<int, 2> setd = {LCA(u, q), LCA(v, q)};
     if(setc == setd) return 1;
     swap(setd[0], setd[1]);
     if(setc == setd) return 1;
     array<int, 2> sete = {LCA(u, v), LCA(p, q)};
     array<int, 2> setf = {LCA(u, LCA(p, q)), LCA(v, LCA(p, q))};
     if (sete == setf) return 1;
     swap(setf[0], setf[1]);
     if (sete == setf) return 1;
     return 0; 
}
bool valid(vector<pii>paths)
{
     for(int i = 0; i < paths.size(); i++)
     {
         for(int j = 0; j < paths.size(); j++)
         {
             if(i == j) continue;
             if(intersect(paths[i].first, paths[i].second, paths[j].first, paths[j].second))
             {
                return false;
             }
         }
     }
     return true; 
}
signed main(void)
{  
    scanf("%d %d", &n, &q);
    for(int i = 1; i <= n; i++)
    {
        fa[i] = i; 
    }
    int cnt = 0;
    for(int i = 0; i < n + 1; i++)
    {
         int u, v; 
         scanf("%d %d", &u, &v);
         if(find(u) == find(v)) 
         {
            if(u > v) swap(u, v); 
            edges[cnt][0] = u; 
            edges[cnt][1] = v; 
            cnt++;
            continue; 
         }
         fa[find(v)] = find(u); 
         adj[u].push_back(v);
         adj[v].push_back(u); 
    }
    dfs(1, 0); 
    for(int i = 0; i < q; i++)
    { 
         int u, v; 
         scanf("%d %d", &u, &v);
         int res = 1; 
         for(int j = 0; j < EXT; j++)
         {
             for(int k = 0; k < EXT; k++)
             {
                 vector<pii>paths; 
                 paths.push_back(mp(u, edges[j][k]));
                 paths.push_back(mp(edges[j][k xor 1], v));
                 res += valid(paths);   
             }
         }
         for(int t = 0; t < EXT; t++)
         {
             swap(edges[0], edges[1]); 
             for (int j = 0; j < EXT; j++)
             {
                 for (int k = 0; k < EXT; k++)
                 {
                     vector<pii> paths;
                     paths.push_back(mp(u, edges[0][j]));
                     paths.push_back(mp(edges[0][j xor 1], edges[1][k]));
                     paths.push_back(mp(edges[1][k xor 1], v));
                     res += valid(paths);
                 }
             }
         }
         printf("%d\n", res); 
    }
    return 0;
}