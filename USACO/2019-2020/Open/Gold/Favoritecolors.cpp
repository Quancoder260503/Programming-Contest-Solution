#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10
#define pii pair<int,int>
#define mp make_pair
int fa[MAXN];
vector<int>adj[MAXN]; 
vector<int>tadj[MAXN]; 
int n, m;
queue<int> q;
int col[MAXN];
void merge(int u, int v)
{
     u = fa[u]; v = fa[v]; 
     if(u == v) return; 
     if(tadj[u].size() < tadj[v].size()) swap(u, v); 
     for(int i = 0; i < tadj[v].size(); i++)
     {
         fa[tadj[v][i]] = u;
         tadj[u].push_back(tadj[v][i]); 
     }
     adj[u].insert(adj[u].end(), adj[v].begin(), adj[v].end());  
     adj[v].clear();
     if(adj[u].size() > 1) q.push(u); 
     return;
}
signed main(void)
{
    scanf("%d %d", &n, &m); 
    for(int i = 1; i <= n; i++)
    {
         fa[i] = i;
         tadj[i].push_back(i);
    }
    for(int i = 0; i < m; i++)
    {
         int u, v; 
         scanf("%d %d", &u, &v);
         adj[u].push_back(v); 
    }
    for(int i = 1; i <= n; i++)
    {
        if(adj[i].size() > 1)
        {
            q.push(i); 
        }
    }
    while(q.size())
    {
         int u = q.front();
         if(adj[u].size() > 1)
         {
             int v = adj[u].back(); 
             adj[u].pop_back(); 
             merge(adj[u].back(), v); 
         }
         else 
         {
             q.pop();
         }
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++)
    {
        if(col[fa[i]] == 0)
        {
            col[fa[i]] = ++cnt; 
        }
        printf("%d\n", col[fa[i]]);
    }
    return 0; 
}