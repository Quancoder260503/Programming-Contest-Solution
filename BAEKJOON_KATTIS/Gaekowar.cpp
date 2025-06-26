#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005
#define mp make_pair
int n, m;
vector<pair<int,int> > adj[MAXN];
int fa[MAXN]; 
int vis[MAXN]; 
void djsktra(int src, vector<int>&dist, bool t, int s1 = 0, int s2 = 0)
{
    fill(dist.begin(), dist.end(), INT_MAX);
    using T = pair<int, int>;
    dist[src] = 0;
    priority_queue<T, vector<T>, greater<T> > pq;
    pq.push(mp(0,src)); 
    while (pq.size())
    {
        int u = pq.top().second;
        int val = pq.top().first;
        pq.pop(); 
        if (val != dist[u]) continue;
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i].first;
            int cost = adj[u][i].second;
            if(t && u == s1 && v == s2) continue; 
            if(t && v == s1 && u == s2) continue;
            if (dist[v] > dist[u] + cost)
            {
                dist[v] = dist[u] + cost;
                fa[v] = u;
                pq.push(mp(dist[v], v));
            }
        }
    }
    return;
}
signed main(void)
{
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= m; i++)
    {
         int u,v,w ; scanf("%d%d%d",&u,&v,&w);
         adj[u].push_back(mp(v,w));
         adj[v].push_back(mp(u,w)); 
    }
    vector<int>dist(n + 1); 
    djsktra(1, dist, 0);
    int ans = 0;
    for(int i = 2; i <= n; i++)
    {
        djsktra(1,dist, 1, i, fa[i]);
        if(ans == INT_MAX) continue; 
        ans = max(ans, dist[n]);  
    }
    printf("%d\n",ans); 
    return 0;
}

/* Analysis: 
   consider the edges will be on the shortest path tree
   we are going to assess the shortest path of the graph without using these edges
   if we remove any edges outside the SPT then the answer will not be different
   Phase 1 : Find the shortest path tree
   Phase 2 : Find the shortest path of the graph without the edges on trees
*/