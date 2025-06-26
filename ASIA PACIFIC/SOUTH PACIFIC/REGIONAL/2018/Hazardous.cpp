#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int) 3e5 + 10; 
#define lint long long
int s, e, n, m; 
lint dist[MAXN];
vector<pair<int,int>>adj[MAXN]; 
struct edge
{
     int u, v, weight, cost;
     edge(int _u, int _v, int _weight, int _cost) : u(_u), v(_v), weight(_weight), cost(_cost) {};  
};
bool cmp(const edge &a, const edge &b)
{
    return a.weight < b.weight;
}
int fa[MAXN];
vector<edge> Edge;
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
void dijsktra(int src)
{
    using T = pair<lint, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    memset(dist, 63, sizeof(dist)); 
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (pq.size())
    {
        pair<lint, int> t = pq.top();
        lint dst = t.first;
        int node = t.second;
        pq.pop();
        if (dist[node] != dst) continue;
        for (int i = 0; i < adj[node].size(); i++)
        {
            int v = adj[node][i].first;
            lint cost = adj[node][i].second;
            if (dist[v] > dist[node] + cost)
            {
                dist[v] = dist[node] + cost;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}
bool f(int max_w)
{
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 0; i < Edge.size(); i++)
    {
        int u = Edge[i].u;
        int v = Edge[i].v;
        int w = Edge[i].weight;
        int cost = Edge[i].cost;
        if(max_w < w) break; 
        if (find(u) == find(v)) continue;
        fa[find(u)] = find(v);
        if (find(e) == find(s))
        {
            return 1; 
        }
    }
    return 0;
}
signed main(void)
{
    cin >> n >> m >> s >> e; 
    for(int i = 0; i < m; i++)
    {
        int u, v, w, l;
        cin >> u >> v >> w >> l; 
        Edge.push_back(edge(u, v, w, l));  
    }
    sort(Edge.begin(), Edge.end(), cmp);
    int max_H = 0;
    int lo = 1; 
    int hi = (int) 1e8; 
    while(lo < hi)
    {
        int mid = (lo + hi) / 2;
        if(f(mid))
        {
            hi = mid; 
        }
        else 
        {
            lo = mid + 1;
        }
    }
    for (int i = 0; i < Edge.size(); i++)
    {
        int u = Edge[i].u;
        int v = Edge[i].v;
        int w = Edge[i].weight;
        int cost = Edge[i].cost;
        if(w > lo) break; 
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    }
    dijsktra(s);
    cout << lo << '\n' << dist[e] << '\n';  
    return 0;
}
// use binary search to get the maximum hazardous