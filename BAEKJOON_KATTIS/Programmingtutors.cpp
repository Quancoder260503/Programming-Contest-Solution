#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN (int) 1e6 + 10
int n, m; 
vector<int>adj[MAXN]; 
bool vis[MAXN]; 
int match[MAXN]; 
typedef struct
{
     int x, y;
} point; 
lint mdist(const point &a, const point &b)
{
     return abs(a.x - b.x) + abs(a.y - b.y); 
}
point arr[MAXN]; 
point tur[MAXN]; 
bool dfs(int u)
{
    if(vis[u]) return false;
    vis[u] = true; 
    for(int i = 0; i < adj[u].size(); i++)
    {
         int v = adj[u][i];
         if(!match[v] || dfs(match[v]))
         {
             match[v] = u; 
             return true; 
         }
    }
    return false;
}
bool solve(lint dist)
{
    for(int i = 1; i <= n; i++)
    {
         match[i] = 0;
         adj[i].clear(); 
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
             if(mdist(arr[i], tur[j]) <= dist)
             {
                 adj[i].push_back(j);
             }
        }
    }
    for(int i = 1; i <= n; i++)
    {
         fill(vis + 1, vis + n + 1, 0);
         dfs(i); 
    }
    for(int i = 1; i <= n; i++)
    {
         if(match[i] == 0) return false;
    }
    return true;
}
signed main(void)
{
    scanf("%d", &n); 
    for(int i = 1; i <= n; i++)
    {
         scanf("%d %d", &arr[i].x, &arr[i].y); 
    }
    for(int i = 1; i <= n; i++)
    {
         scanf("%d %d", &tur[i].x, &tur[i].y); 
    }
    lint lo = 0; 
    lint hi = 1e10; 
    while(lo < hi)
    {
         lint mid = (lo + hi) / 2; 
         if(solve(mid))
         {
             hi = mid;
         }
         else
         {
             lo = mid + 1;
         }
    }
    printf("%lld\n", lo); 
    return 0; 
}