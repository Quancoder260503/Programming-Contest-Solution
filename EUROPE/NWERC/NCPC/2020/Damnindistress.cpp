#include "bits/stdc++.h"
using namespace std;
#define mod (int)1e9 + 7
#define lint long long
#define MAXN (int)1e6 + 10
lint n,w;
struct arr
{
    lint cap;
    lint flow;
};
vector<int>adj[MAXN];
arr arr[MAXN];  
lint dfs(int u, int add)
{
     if(! (int)adj[u].size())
     {
          return add + arr[u].flow >= arr[u].cap ? add + arr[u].flow : 0; 
     }
     lint toflow = 0; 
     for(int i = 0; i < adj[u].size(); i++)
     {
         int v = adj[u][i];
         toflow = max(dfs(v, add), toflow);
     }
     lint res = max(toflow + arr[u].flow, add + arr[u].flow); 
     return  res >= arr[u].cap ? res: 0; 
}
bool good(lint x)
{
     lint tot = 0; 
     for(int i = 0; i < adj[0].size(); i++)
     {
         tot = max(dfs(adj[0][i], x), tot); 
     }
     return tot >= w; 
}
signed main(void)
{
    scanf("%lld %lld", &n, &w);
    for(int i = 1; i <= n; i++)
    {
         int u;
         scanf("%d %lld %lld", &u, &arr[i].cap, &arr[i].flow); 
         adj[u].push_back(i); 
    } 
    lint lo = 0;
    lint hi = (lint) w; 
    while(lo < hi)
    {
         lint  mid = (lo + hi) / 2; 
         if(good(mid))
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