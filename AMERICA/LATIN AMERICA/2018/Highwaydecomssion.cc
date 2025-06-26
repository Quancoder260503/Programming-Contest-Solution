#include "bits/stdc++.h"

using namespace std; 
const int64_t INF = 1e15; 

int main(void)
{
    int N, M;
    cin >> N >> M;
    vector<int>C(N, (int) 1e9); 
    vector<vector<tuple<int, int, int>>>adj(N); 
    vector<int64_t>dist(N); 
    for(int i = 0; i < M; i++)
    {
        int U, V, L, C; 
        cin >> U >> V >> L >> C; 
        --U, --V;
        adj[U].push_back({V, L, C});
        adj[V].push_back({U, L, C}); 
    }
    auto dijsktra = [&](int src)
    {
        using T = pair<int64_t, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        fill(dist.begin(), dist.end(), INF);
        dist[src] = 0;
        pq.push({0, src});
        while (pq.size())
        {
            auto [tdist, u] = pq.top();
            pq.pop();
            if (tdist != dist[u]) continue;
            for (auto [v, len, cost] : adj[u])
            {
                if (dist[v] == 1LL * (dist[u] + len))
                {
                    C[v] = min(C[v], cost); 
                   // fa[v].push_back({u, cost});
                }
                else if (dist[v] > 1LL * (dist[u] + len))
                {
                    dist[v] = 1LL * (dist[u] + len);
                    // fa[v].clear();
                    // fa[v].push_back({u, cost});
                    C[v] = cost;
                    pq.push({dist[v], v});
                }
            }
        }
    };
    C[0] = 0; 
    dijsktra(0);
    int64_t ret = accumulate(C.begin(), C.end(), 0LL); 
    cout << ret << '\n'; 
    return 0; 
}