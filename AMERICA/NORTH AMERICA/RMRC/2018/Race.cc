#include "bits/stdc++.h"

using namespace std; 

const int64_t oo = LLONG_MAX / 4; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int N, M; 
    cin >> N >> M;
    string color = "ROYGBIV"; 
    vector<vector<tuple<int, int, char>>>g(N); 
    int X, Y, W; 
    char C; 
    for(int i = 0; i < M; i++) { 
        cin >> X >> Y >> W >> C; 
        --X, --Y; 
        g[X].push_back({Y, W, C}); 
        g[Y].push_back({X, W, C}); 
    }
    using T = pair<int, pair<int, int>>; 
    priority_queue<T, vector<T>, greater<T>>pq; 
    vector<vector<int64_t>>dist(N, vector<int64_t>(1 << 7, oo));
    dist[0][0] = 0; 
    pq.push({0, {0, 0}}); 
    while(pq.size()) { 
        auto [d, x] = pq.top(); 
        pq.pop(); 
        auto [u, mask] = x; 
        if(dist[u][mask] != d) continue; 
        for(auto [v, w, C] : g[u]) { 
            int c = color.find(C); 
            if(dist[v][mask | (1 << c)] > dist[u][mask] + w) { 
                dist[v][mask | (1 << c)] = dist[u][mask] + w; 
                pq.push({dist[v][mask | (1 << c)], {v, mask | (1 << c)}});
            }
        }
    }
    cout << dist[0][(1 << 7) - 1] << '\n'; 
    return 0; 
}