#include "bits/stdc++.h"
using namespace std;
#define mp make_pair 
#define pii pair<int,int> 
#define lint long long
const int MAXN = (int) 4e5 + 10; 
vector<pair<int, pii> > edges; 
int n, m; 
int fa[MAXN]; 
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]); 
}
signed main(void)
{
    cin >> n >> m; 
    iota(fa + 1, fa + n + m + 2, 1); 
    for(int i = 1; i <= m; i++)
    {
      int at, cost; 
      cin >> at >> cost;
      edges.push_back(mp(cost, mp(at, n + i))); 
      edges.push_back(mp(0, mp(n + i, n + m + 1))); 
    }
    for(int i = 1; i <= n; i++)
    {
        int cost; cin >> cost;
        edges.push_back(mp(cost, mp(i, i == n ? 1 : i + 1))); 
    }
    sort(edges.begin(), edges.end());
    lint ans = 0;  
    for(int i = 0; i < edges.size(); i++)
    {
        int w = edges[i].first; 
        int u = edges[i].second.first; 
        int v = edges[i].second.second; 
        if(find(u) == find(v)) continue; 
        fa[find(u)] = find(v); 
        ans += w;
    }
    cout << ans << "\n"; 
    return 0; 
}