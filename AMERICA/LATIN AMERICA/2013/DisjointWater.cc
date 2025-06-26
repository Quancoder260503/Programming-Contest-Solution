#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int N, M; 
    cin >> N >> M;
    vector<vector<int>>g(N + 1);   
    vector<int>par(N + 1), w(N + 1); 
    for(int i = 0, U, V; i < M; i++) { 
        cin >> U >> V;
        if(U == 1) { 
            par[V] = V; 
        }
        else { 
            g[V].push_back(U); 
        }
    }
    function<int(int)> F = [&](int u) -> int { 
        return par[u] == u ? u : par[u] = F(par[u]);  
    };
    for(int v = 2; v <= N; v++) { 
        for(auto u : g[v]) { 
            if(!par[v]) { par[v] = u; }
            else if(F(u) != F(v)) {
                par[v] = v; 
            }
        }
    }
    for(int i = 2; i <= N; i++) { 
        w[F(i)]++; 
    }
    int64_t ret = 0; 
    for(int i = 1; i <= N; i++) { 
        ret += 1LL * w[i] * (N - 1 - w[i]); 
    }
    ret = ret / 2; 
    cout << ret + N - 1 << '\n'; 
    return 0; 
}