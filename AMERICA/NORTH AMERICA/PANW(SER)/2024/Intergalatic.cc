#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e9; 

int main(void) { 
 int N, M, K; 
 cin >> N >> M >> K; 
 vector<int>par(N),comp(N); 
 vector<int64_t>cnt(N); 
 iota(par.begin(), par.end(), 0); 
 fill(comp.begin(), comp.end(), 1); 
 function<int(int)> F = [&](int u) { 
  return u == par[u] ? u : par[u] = F(par[u]); 
 }; 
 for(int i = 0, u, v; i < M; i++) { 
  cin >> u >> v;
  --u, --v; 
  if(F(u) == F(v)) { 
   cnt[F(u)]++; 
   continue; 
  } 
  u = F(u), v = F(v); 
  par[v] = u; 
  comp[u] += comp[v]; 
  cnt[u] += 1 + cnt[v]; 
 }
 int ret = 0;
 int64_t nEdge = 1LL * K  * (K - 1);  
// cout << (1LL * K * (K - 1) / 2) << '\n'; 
 for(int i = 0; i < N; i++) { 
  if(F(i) == i && comp[i] == K && cnt[i] == nEdge) { 
    ret++; 
  } 
 }
 cout << ret << '\n';  
 return 0;
}