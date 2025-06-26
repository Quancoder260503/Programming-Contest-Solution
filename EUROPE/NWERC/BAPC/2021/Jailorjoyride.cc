#include "bits/stdc++.h"

using namespace std;

const int64_t INF = 1e14; 

const int maxf = 750; 

int64_t d[maxf][maxf], adj[maxf][maxf], dyn[maxf], dist[maxf]; 
vector<int>g[maxf];
int leaf[maxf]; 

int main(void)
{
    int n, m, s, t; 
    cin >> n >> m >> s >> t;
    for(int i = 0; i < maxf; i++) for(int j = 0; j < maxf; j++) if(i != j) d[i][j] = INF; 
    for(int i = 0; i < m; i++)
    {
        int U, V, W; 
        cin >> U >> V >> W; 
        adj[U][V] = adj[V][U] = 1; 
        d[U][V] = d[V][U] = W; 
    }
    for(int k = 1; k <= n; k++) for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++)
    {
        if(d[i][k] == INF || d[k][j] == INF) continue; 
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
    }
    for(int i = 1; i <= n; i++)
    {
        int64_t mx_dist = 0; 
        for(int j = 1; j <= n; j++) if(d[i][j] < INF) mx_dist = max(mx_dist, d[i][j]); 
        dist[i] = mx_dist; 
        for(int j = 1; j <= n; j++) if(i != j && d[i][j] == mx_dist)
        {
            g[i].push_back(j); 
        }
        leaf[i] = accumulate(adj[i], adj[i] + maxf, 0) == 1; 
    }
    if(leaf[t])
    {
        cout << d[s][t] << '\n'; 
        return 0; 
    }
    for(int i = 1; i <= n; i++) dyn[i] = (leaf[i] ? 0 : INF); 
    vector<int>fa(n + 1); 
    int artic = -1; 
    function<int(int)>find = [&](int u) -> int 
    {
        return fa[u] == u ? u : fa[u] = find(fa[u]); 
    };
    for(int k = 1; k <= n; k++)
    {
        iota(fa.begin(), fa.end(), 0); 
        for(int x = 1; x <= n; x++) for(int y = 1; y <= n; y++)
        {
            if(!adj[x][y]) continue; 
            if(x == k && y == t) continue; 
            if(x == t && y == k) continue;  
            fa[find(x)] = find(y); 
        }
        if(find(s) != find(t))
        {
            artic = k; 
            break; 
        }
    }
    int64_t mx_dist = -INF;
    for(int i = 1; i <= n; i++) if(i != t && d[t][i] < INF && find(t) == find(i))
    {
        mx_dist = max(mx_dist, d[t][i]); 
    }
    vector<int>st;
    for(int i = 1; i <= n; i++) if(i != t && d[t][i] == mx_dist && find(t) == find(i))
    {
        st.push_back(i); 
    }
    vector<int>col(n + 1); 
    function<void(int)>doit = [&](int u)
    {
        if(col[u] == 1)
        {
            dyn[u] = INF; 
            return;    
        }
        if(col[u] == 2) return; 
        dyn[u] = 0; 
        col[u] = 1; 
        if(!leaf[u])
        {
            for(auto v : g[u])
            {
                doit(v); 
                dyn[u] = max(dyn[u], dyn[v] + dist[u]); 
            }
        }
        col[u] = 2;
        return; 
    }; 
    int64_t ret = 0; 
    for(auto v : st) 
    {
        doit(v); 
        ret = max(ret, dyn[v]); 
    }
    if(ret >= INF)
    {
        cout << "impossible" << '\n'; 
        return 0; 
    }
    ret += mx_dist + d[s][t]; 
    cout << ret << '\n'; 
    return 0; 
}