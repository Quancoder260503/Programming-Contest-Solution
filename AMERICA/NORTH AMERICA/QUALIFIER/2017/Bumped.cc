#include "bits/stdc++.h"

using namespace std;

const int64_t maxf = 2e5 + 2; 

const int64_t oo = 3e9; 

vector<pair<int64_t, int64_t>>g[maxf];
vector<int64_t>adj[maxf]; 
int64_t N, M, f, S, T, U, V, W; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    cin >> N >> M >> f >> S >> T; 
    for(int64_t i = 0; i < M; i++) { 
        cin >> U >> V >> W; 
        g[U].push_back({V, W}); 
        g[V].push_back({U, W}); 
    }
    for(int64_t i = 0; i < f; i++) { 
        cin >> U >> V; 
        adj[U].push_back(V); 
       // adj[V].push_back(U); 
    }
    vector<vector<int64_t>>dist(N, vector<int64_t>(2, oo));
    dist[S][0] = 0; 
    using Tup = tuple<int64_t, int64_t, int64_t>; 
    priority_queue<Tup, vector<Tup>, greater<Tup>>pq; 
    pq.push({0, S, 0}); 
    while(pq.size()) { 
        auto [dst, u, used] = pq.top(); 
        pq.pop(); 
        if(dist[u][used] != dst) continue; 
        for(auto [v, w] : g[u]) if(dist[v][used] > dist[u][used] + w) {
            dist[v][used] = dist[u][used] + w;
            pq.push({dist[v][used], v, used});
        }
        if(!used) { 
            for(auto v : adj[u]) if(dist[v][1] > dist[u][used]) { 
                dist[v][1] = dist[u][used]; 
                pq.push({dist[v][1], v, 1}); 
            }
        }
    }
    cout << min(dist[T][0], dist[T][1]) << '\n'; 
    return 0;
}