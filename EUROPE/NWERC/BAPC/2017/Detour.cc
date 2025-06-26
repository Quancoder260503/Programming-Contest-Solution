#include "bits/stdc++.h"
using namespace std; 
const int64_t INF = 1e14; 
int main(void)
{
    int N, M; 
    while(cin >> N >> M)
    {
        vector<int64_t>dist(N);
        vector<vector<int>>fa(N); 
        auto dijsktra = [&](int src, vector<vector<pair<int, int64_t>>> &adj)
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
                for (auto [v, cost] : adj[u])
                {
                    if (dist[v] == 1LL * (dist[u] + cost))
                    {
                        fa[v].push_back(u);
                    }
                    else if (dist[v] > 1LL * (dist[u] + cost))
                    {
                        dist[v] = 1LL * (dist[u] + cost);
                        fa[v].clear();
                        fa[v].push_back(u);
                        pq.push({dist[v], v});
                    }
                }
            }
        };
        vector<vector<pair<int, int64_t>>>adj(N), nadj(N); 
        vector<tuple<int, int, int64_t>>edge; 
        for(int i = 0; i < M; i++)
        {
            int U, V; 
            int64_t C;
            cin >> U >> V >> C; 
            adj[U].push_back({V, C});  
            adj[V].push_back({U, C}); 
            edge.push_back({U, V, C}); 
        }
        dijsktra(1, adj);
        map<pair<int, int>,int>ctr; 
        for(int i = 0; i < N; i++) for(auto v : fa[i])
        {
            ctr[{i, v}] = 1; 
        }
        for(int i = 0; i < N; i++) fa[i].clear(); 
        for(auto [U, V, C] : edge)
        {
            if(!ctr.count({U, V})) nadj[U].push_back({V, C});
            if(!ctr.count({V, U})) nadj[V].push_back({U, C});
        }
        dijsktra(0, nadj); 
        if(dist[1] == INF)
        {
            cout << "impossible" << '\n'; 
        }
        else 
        {
            vector<int>ret; 
            int curr = 1; 
            while(curr != 0)
            {
                ret.push_back(curr); 
                assert(fa[curr].size()); 
                curr = fa[curr][0]; 
            }
            ret.push_back(curr); 
            reverse(ret.begin(), ret.end()); 
            cout << ret.size() << ' '; 
            for(auto it : ret) cout << it << " "; 
            cout << '\n'; 
        }
    }
    return 0; 
}
