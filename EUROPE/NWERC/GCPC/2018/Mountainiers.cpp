#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 2e5 + 10
#define mp make_pair
#define M 502
#define MASK 17
int n,m,q; 
int g[M][M]; 
int dx[4] = {1,-1,0,0}; 
int dy[4] = {0,0,-1,1}; 
int fa[MAXN];
int up[MASK][MAXN];
int val[MASK][MAXN];  
vector<pair<int,int> >adj[MAXN]; 
int dep[MAXN]; 
struct edge
{
   int u,v,w; 
   edge(int _w, int _u, int _v) : w(_w), u(_u), v(_v) {}  
}; 
int hsh(int i, int j)
{
     return (i - 1) * m + j; 
}
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
bool cmp(const edge &a, const edge &b)
{ 
    return a.w < b.w; 
}
void dfs(int u, int p)
{
     for(int i = 1; i < MASK; i++)
     {
         up[i][u] = up[i - 1][up[i - 1][u]]; 
     }
     for(int i = 0; i < (int) adj[u].size(); i++)
     {
         int v = adj[u][i].first;
         if(v == p) continue; 
         val[0][v] = adj[u][i].second; 
         dep[v] = dep[up[0][v] = u] + 1; 
         dfs(v,u); 
     }
}
int lca(int u, int v)
{
     if(dep[u] < dep[v]) swap(u,v); 
     int dist = dep[u] - dep[v];
     for(int i = 0; i < MASK; i++)
     {
         if(dist & (1 << i)) u = up[i][u]; 
     }
     if(u == v) return u; 
     for(int i = MASK - 1; i >= 0; i--)
     {
         int tu = up[i][u]; int tv = up[i][v];
         if(tu != tv)
         {
             u = tu; v = tv;
         }
     }
     return up[0][u]; 
}
int jump(int u, int dist)
{
     int ans = 0;
     for(int i = 0; i < MASK; i++)
     {
         if(dist & (1 << i))
         {
             ans = max(ans, val[i][u]);
             u = up[i][u]; 
         }
     }
     return ans;
}
signed main(void)
{
    scanf("%d%d%d",&n,&m,&q);
    vector<edge>ed;
    for(int i = 1; i <= n * m; i++)
    {
         fa[i] = i; 
    }
    for(int i = 1; i <= n; i++)
    {
         for(int j = 1; j <= m; j++)
         {
             scanf("%d",&g[i][j]);  
         }
    }
    for(int i = 1; i <= n; i++)
    {
         for(int j = 1; j <= m; j++)
         {
             for(int k = 0; k < 4; k++)
             {
                 int tx = i + dx[k];
                 int ty = j + dy[k]; 
                 if(tx < 1 || tx > n) continue; 
                 if(ty < 1 || ty > m) continue; 
                 ed.push_back(edge(max(g[i][j],g[tx][ty]),hsh(i,j),hsh(tx,ty))); 
             }   
         }
    }
    sort(ed.begin(),ed.end(),cmp); 
    for(int i = 0; i < ed.size(); i++)
    {
         int u = ed[i].u; int v = ed[i].v; 
         int w = ed[i].w; 
         if(find(u) == find(v)) continue; 
         fa[find(v)] = find(u); 
         adj[u].push_back(mp(v,w)); 
         adj[v].push_back(mp(u,w)); 
    }
    dfs(1,0);
    for(int i = 1; i < MASK; i++)
    {
         for(int j = 1; j <= n * m; j++)
         {
             val[i][j] = max(val[i - 1][j], val[i - 1][up[i - 1][j]]);
         }
    } 
    int ans,anc;
    for(int i = 1; i <= q; i++)
    {
        int x,y,tx,ty;
        scanf("%d%d%d%d",&x,&y,&tx,&ty); 
        if(x == tx && y == ty)
        {
             printf("%d\n",g[x][y]); 
        }
        else
        {
          int anc = lca(hsh(x,y), hsh(tx,ty));
          ans = max(jump(hsh(x,y), dep[hsh(x,y)] - dep[anc]), jump(hsh(tx,ty), dep[hsh(tx,ty)] - dep[anc])); 
          printf("%d\n",ans); 
        }
    }
    return 0; 
}