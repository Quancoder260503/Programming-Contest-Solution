#include "bits/stdc++.h"

using namespace std;

const int maxf = 3e5 + 10; 

vector<int>g[maxf], g2[maxf]; 
int64_t dyn[2][maxf], dyn2[2][maxf], distA[maxf], distB[maxf], suffix[maxf]; 

void dfs(int u = 0, int p = -1){
    for(auto v : g[u]) if(v != p) {  
        dfs(v, u);
        if(dyn[0][v] + 1 > dyn[0][u]) {
            dyn[1][u] = dyn[0][u];
            dyn[0][u] = dyn[0][v] + 1;
        }
        else if(dyn[0][v] + 1 > dyn[1][u]){
            dyn[1][u]= dyn[0][v] + 1;
        }
    }
    return; 
}
void dfs2(int u = 0, int p = -1, int64_t w = 0){
    distA[u] = max(w, dyn[0][u]);
    for(auto v : g[u]){
        if(v == p) continue;
        if(dyn[0][u] == dyn[0][v] + 1) dfs2(v, u, max(w, dyn[1][u]) + 1);
        else dfs2(v, u, distA[u] + 1);
    }
    return; 
} 

void dfs1(int u = 0, int p = -1){
    for(auto v : g2[u]) if(v != p) {  
        dfs1(v, u);
        if(dyn[0][v] + 1 > dyn[0][u]) {
            dyn[1][u] = dyn[0][u];
            dyn[0][u] = dyn[0][v] + 1;
        }
        else if(dyn[0][v] + 1 > dyn[1][u]){
            dyn[1][u]= dyn[0][v] + 1;
        }
    }
    return; 
}
void dfs3(int u = 0, int p = -1, int64_t w = 0){
    distB[u] = max(w, dyn[0][u]);
    for(auto v : g2[u]){
        if(v == p) continue;
        if(dyn[0][u] == dyn[0][v] + 1) dfs3(v, u, max(w, dyn[1][u]) + 1);
        else dfs3(v, u, distB[u] + 1);
    }
    return; 
} 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int N, M; 
    cin >> N >> M; 
    for(int i = 0, U, V; i < N - 1; i++) {
        cin >> U >> V; 
        --U, --V; 
        g[U].push_back(V); 
        g[V].push_back(U); 
    }
    for(int i = 0, U, V; i < M - 1; i++) {
        cin >> U >> V; 
        --U, --V; 
        g2[U].push_back(V); 
        g2[V].push_back(U); 
    }
    dfs(); 
    dfs2(); 
    memset(dyn, 0, sizeof(dyn)); 
    dfs1();
    dfs3(); 
    int64_t dim = 0; 
    for(int i = 0; i < N; i++) { 
        dim = max(dim, distA[i]); 
    }
    for(int i = 0; i < M; i++) { 
        dim = max(dim, distB[i]); 
    }
    sort(distA, distA + N); 
    sort(distB, distB + M);
    double ret = 0; 
    for(int i = M - 1; i >= 0; i--) { 
        suffix[i] = suffix[i + 1] + distB[i]; 
    }
    for(int i = 0; i < N; i++) { 
        int pos = upper_bound(distB, distB + M, dim - 1 - distA[i]) - distB; 
        ret += double(suffix[pos] + 1LL * (1 + distA[i]) * (M - pos)) / double(1LL * N * M) + 
               double(1LL * dim * pos) / double(1LL * N * M);   
    }
    cout << fixed << setprecision(3) << ret << '\n';  
    return 0; 
}