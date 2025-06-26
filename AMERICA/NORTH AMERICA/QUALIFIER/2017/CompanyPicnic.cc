#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 10; 

vector<vector<int>>g;
vector<vector<pair<int, double>>>dyn;  
vector<string>par;
int N, M; 
string U, V; 
map<string, int>mp; 
vector<double>W; 

void dfs(int u) { 
    for(auto v : g[u]) { 
        dfs(v); 
        dyn[u][0].first    += dyn[v][1].first; 
        dyn[u][0].second   += dyn[v][1].second; 
    }
    dyn[u][1] = dyn[u][0]; 
    for(auto v : g[u]) { 
        dyn[u][1] = max(dyn[u][1], {dyn[u][0].first - dyn[v][1].first + 1 + dyn[v][0].first, 
                                    dyn[u][0].second - dyn[v][1].second + dyn[v][0].second + min(W[u], W[v])}); 
    }
    return;  
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    cin >> N; 
    M = 0; 
    int root = 0; 
    g.resize(N); 
    W.resize(N);  
    dyn.resize(N, vector<pair<int, double>>(2));
    par.resize(N); 
    for(int i = 0; i < N; i++) { 
        cin >> U >> W[i] >> par[i];
        mp[U] = i;  
    }
    for(int i = 0; i < N; i++) { 
        if(par[i] == "CEO") { 
            root = i; 
        }
        else { 
            g[mp[par[i]]].push_back(i); 
        }
    }
    dfs(root);
    cout << dyn[root][1].first << " " << fixed << setprecision(10) << dyn[root][1].second / dyn[root][1].first << '\n';  
    return 0; 
}