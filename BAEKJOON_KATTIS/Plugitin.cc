#include "bits/stdc++.h"

using namespace std;

const int N = 5e3 + 2;
const int INF = 1e8 + 5;

bool vis[N]; 
int n, m, k, where[N], match[N], dist[N], str[N];
vector<int> g[N], h[N], paths[N], ord;

bool doit(int u)
{
    if (vis[u]) return false;
    vis[u] = true;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!match[v] | doit(match[v]))
        {
            match[v] = u;
            return true;
        }
    }
    return false;
}
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (cin >> n >> m >> k)
    {
        for (int i = 0; i < k; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
        }
        int ret = 0, res = 0;
        for(int i = 1; i <= n; i++) 
        {
            memset(vis, 0, sizeof(vis)); 
            res += doit(i); 
        }
        ret = res; 
        for(int i = 1; i <= m; i++) str[i] = match[i]; 
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++) match[j] = str[j];
            memset(vis, 0, sizeof(vis));
            int curr = doit(i);
            memset(vis, 0, sizeof(vis));
            curr += doit(i);
            ret = max(ret, res + curr); 
        }
        cout << ret << '\n'; 
    }
    return 0;
}