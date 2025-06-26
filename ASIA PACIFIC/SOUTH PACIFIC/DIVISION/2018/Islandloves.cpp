#include "bits/stdc++.h"
using namespace std;
#define mp make_pair
#define pii pair<int, int>
const int MAXN = 2e5 + 10;
set<pii> edges;
int n, m, q;
int fa[MAXN];
vector<pair<pii, int> > queries;
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}
signed main(void)
{
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        if (u > v)
            swap(u, v);
        edges.insert(mp(u, v));
    }
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 0; i < q; i++)
    {
        char type;
        int u, v;
        cin >> type >> u >> v;
        if (u > v)
            swap(u, v);
        if (type == 'E')
        {
            edges.erase(mp(u, v));
        }
        queries.push_back(mp(mp(u, v), type == 'E' ? -1 : 1));
    }
    reverse(queries.begin(), queries.end());
    for (auto it : edges)
    {
        if (find(it.second) == find(it.first)) continue;
        fa[find(it.second)] = find(it.first);
    }
    vector<string>ans;
    for (int i = 0; i < q; i++)
    {
        int u = queries[i].first.first;
        int v = queries[i].first.second;
        if(queries[i].second == -1)
        {
            if(find(u) == find(v)) continue; 
            fa[find(u)] = find(v); 
        }
        else
        {
            if(find(u) == find(v))
            {
                ans.push_back("YES");
            }
            else
            {
                ans.push_back("NO"); 
            }
        }
    }
    reverse(ans.begin(), ans.end());
    for(auto it : ans)
    {
        cout << it << '\n'; 
    }
    return 0;
}