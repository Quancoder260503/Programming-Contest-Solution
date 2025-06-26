#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10
vector<int>adj[MAXN]; 
#define pii pair<int,int>
#define mp make_pair 
int dist[MAXN]; 
int arr[MAXN]; 
vector<int>fa[MAXN];
int n, m, k; 
char ans[MAXN]; 
vector<int>tadj[MAXN]; 
void djsktra(int src)
{
     priority_queue<pii, vector<pii>, greater<pii> >pq; 
     fill(dist, dist + MAXN, INT_MAX); 
     dist[src] = arr[src];
     pq.push(mp(dist[src], src)); 
     while(pq.size())
     {
         int tval = pq.top().first; 
         int u = pq.top().second; 
         pq.pop(); 
         if(dist[u] != tval) continue; 
         for(int i = 0; i < adj[u].size(); i++)
         {
             int v = adj[u][i];
             if(dist[v] > dist[u] + arr[v])
             {
                 dist[v] = dist[u] + arr[v];
                 fa[v].clear();
                 fa[v].push_back(u);
                 pq.push(mp(dist[v], v)); 
             }
             else if(dist[v] == dist[u] + arr[v])
             {
                 fa[v].push_back(u); 
             }
        }
    } 
} 
vector<int>topo; 
bool vis[MAXN]; 
void dfs2(int u)
{
     if(u == 1) return;
     for(int i = 0; i < fa[u].size(); i++)
     {
         int v = fa[u][i];
         tadj[v].push_back(u); 
         dfs2(v); 
     }
     return;
}
void dfs(int u)
{
     vis[u] = 1; 
     for(int i = 0; i < tadj[u].size(); i++)
     {
         int v = tadj[u][i]; 
         if(vis[v]) continue; 
         dfs(v); 
     }
     topo.push_back(u); 
}
signed main(void)
{
   scanf("%d %d %d", &n, &m, &k);
   for(int i = 1; i <= n; i++)
   {
      scanf("%d", arr + i); 
   }
   for(int i = 0; i < m; i++)
   {
       int u,v; 
       scanf("%d %d", &u, &v);
       adj[u].push_back(v);
       adj[v].push_back(u); 
   }    
   djsktra(1);
   dfs2(n); 
   dfs(1); 
   if(k < n - k)
   {
        int cur = n - k;
        for(int i = 0; i < topo.size(); i++)
        {
             if(cur > 0)
             {
                ans[topo[i] - 1] = 'S'; 
                cur--;
             }
             else 
             {
                ans[topo[i] - 1] = 'N'; 
             }
        }
        for(int i = 0; i < n; i++)
        {
             if(ans[i] == NULL)
             {
                ans[i] = (cur > 0 ? 'S' : 'N');
                cur--;
             }
        }
   }
   else 
   {
        int cur = k;
        for (int i = 0; i < topo.size(); i++)
        {
             if (cur > 0)
             {
                ans[topo[i] - 1] = 'N';
                cur--;
             }
             else
             {
                ans[topo[i] - 1] = 'S';
             }
        }
        for (int i = 0; i < n; i++)
        {
             if (ans[i] == NULL)
             {
                ans[i] = (cur > 0 ? 'N' : 'S');
                cur--;
             }
        }
   }
   if(n == 2 && k == 1)
   {
      puts("impossible"); 
      return 0;
   }
   printf("%s", ans); 
   return 0; 
}
/*
    we need to find all the shortest path lead from 1 to N
    Greedy strategy : 
         We have to make sure that all adjacent edge to 1 and N 
         have to have the same color to 1 and N, respectively. 
*/