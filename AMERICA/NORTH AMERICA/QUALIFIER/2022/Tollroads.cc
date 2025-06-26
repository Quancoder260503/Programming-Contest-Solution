#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
const int K = 23;
vector<pair<int, int>> adj[MAXN];
int up[K][MAXN];
int dyn[K][MAXN]; 
int dep[MAXN];
void dfs(int u, int p)
{
    for (int i = 1; i < K; i++)
    {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int i = 0; i < adj[u].size(); i++)
    {
        auto [v, w] = adj[u][i];
        if (v == p) continue;
        dep[v] = dep[up[0][v] = u] + 1;
        dyn[0][v] = w; 
        dfs(v, u);
    }
    return;
}
int LCA(int u, int v)
{
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; i < K; i++)
    {
        if (d & (1 << i))
        {
            u = up[i][u];
        }
    }
    if (u == v) return u;
    for (int i = K - 1; i >= 0; i--)
    {
        int tu = up[i][u], tv = up[i][v];
        if (tu != tv) u = tu, v = tv;
    }
    return up[0][u];
}
int dist(int u, int v)
{
    return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
}
signed main(void)
{
    int N, M, Q; 
    while(cin >> N >> M >> Q)
    {
        vector<array<int32_t, 3>>edge;
        for(int i = 0; i < M; i++)
        {
            int U, V, W; 
            cin >> U >> V >> W; 
            --U, --V;
            edge.push_back({W, U, V}); 
        }
        vector<int>fa(N); 
        vector<int>comp(N, 1); 
        iota(fa.begin(), fa.end(), 0); 
        function<int(int)>find; 
        find = [&](int u) -> int 
        {
            return u == fa[u] ? u : fa[u] = find(fa[u]); 
        }; 
        auto join = [&](int u, int v)
        {
            u = find(u), v = find(v); 
            if(u == v) return 0;
            if(comp[u] > comp[v]) swap(u, v);  
            fa[u] = v; 
            comp[v] += comp[u]; 
            return 1;
        };
        sort(edge.begin(), edge.end()); 
        for(auto [W, U, V] : edge)
        {
            if(join(U, V))
            {
                adj[U].push_back({V, W});
                adj[V].push_back({U, W}); 
            }
        }
        dfs(0, -1); 
        for(int i = 1; i < K; i++)
        {
            for(int j = 0; j < N; j++)
            {
                dyn[i][j] = max(dyn[i - 1][j], dyn[i - 1][up[i - 1][j]]); 
            }
        }
        auto get_path = [&](int u, int d)
        {
            int ret = 0; 
            for(int i = 0; i < K; i++)
            {
                if(d & (1 << i))
                {
                    ret = max(ret, dyn[i][u]);
                    u = up[i][u]; 
                }
            }
            return ret; 
        }; 
        vector<pair<int, int>>ret(Q); 
        for(int i = 0; i < Q; i++)
        {
            int U, V;
            cin >> U >> V; 
            --U, --V;
            int anc = LCA(U, V); 
            ret[i].first = max(get_path(U, dep[U] - dep[anc]), get_path(V, dep[V] - dep[anc]));
            edge.push_back({ret[i].first, U + N, i});  
        }
        sort(edge.begin(), edge.end());
        iota(fa.begin(), fa.end(), 0); 
        fill(comp.begin(), comp.end(), 1); 
        for(auto [W, U, V] : edge)
        {
            if(U < N)
            {
                join(U, V); 
            }
            else 
            {
                U = U - N; 
                ret[V].second = comp[find(U)]; 
            }
        } 
        for(int i = 0; i < Q; i++)
        {
            cout << ret[i].first << " " << ret[i].second << '\n'; 
        }
    }
    return 0; 
}