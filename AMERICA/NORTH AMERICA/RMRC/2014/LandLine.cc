#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int N, M, K; 
    cin >> N >> M >> K; 
    vector<int>insecure(N, false); 
    for(int i = 0, x; i < K; i++) { 
        cin >> x; 
        insecure[--x] = true; 
    }
    vector<tuple<int, int, int>>edge; 
    for(int i = 0, u, v, w; i < M; i++) {
        cin >> u >> v >> w;  
        edge.push_back({w, --u, --v});
    }
    sort(edge.begin(), edge.end()); 
    vector<int>par(N), c_size(N); 
    iota(par.begin(), par.end(), 0);
    fill(c_size.begin(), c_size.end(), 1);   
    function<int(int)> F = [&](int u) { 
        return par[u] == u ? u : par[u] = F(par[u]); 
    };
    int ret = 0; 
    auto join = [&](int u, int v, int w) {
        u = F(u), v = F(v); 
        if(u == v) return; 
        if(c_size[u] < c_size[v]) swap(u, v); 
        c_size[u] += c_size[v]; 
        par[v] = u; 
        ret += w;  
        return; 
    }; 
    for(auto [w, u, v] : edge) { 
        if(insecure[u] || insecure[v]) continue;
        join(u, v, w); 
    }
    for(auto [w, u, v] : edge) {
        if(insecure[u] && insecure[v]) continue;  
        else if(insecure[u]) { 
            if(c_size[F(u)] > 1) continue; 
            join(u, v, w); 
        }
        else if(insecure[v]) { 
            if(c_size[F(v)] > 1) continue; 
            join(u, v, w); 
        }
    }
    if(c_size[F(0)] < N && K < N) { 
        cout << "impossible\n"; 
    }
    else { 
        if(K == 2) { 
            for(auto [w, u, v] : edge) { join(u, v, w); }
        }
        cout << ret << '\n'; 
    }
    return 0; 
}