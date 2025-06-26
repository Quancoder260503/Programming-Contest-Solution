#include "bits/stdc++.h"

using namespace std; 

const int64_t oo = int64_t(1e12); 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M, K, W; 
 cin >> N >> M >> K >> W; 
 vector<int>marked(N); 
 for(int i = 0; i < K; i++) { 
  int s; cin >> s; 
  marked[--s] = true; 
 }
 vector<array<int, 4>>edge; 
 for(int i = 0, U, V, W; i < M; i++) { 
  cin >> U >> V >> W;
  --U, --V; 
  edge.push_back({W, U, V, marked[U] ^ marked[V]}); 
 }
 vector<int>par(N), comp(N);  
 function<int(int)> F = [&](int u) { 
  return u == par[u] ? u : par[u] = F(par[u]); 
 }; 
 auto merge = [&](int u, int v) -> bool { 
  int fu = F(u), fv = F(v); 
  if(fu == fv) return false; 
  if(comp[fu] > comp[fv]) swap(fu, fv); 
  comp[fv] += comp[fu]; 
  par[fu] = fv; 
  return true; 
 }; 
 auto kruskal = [&]() {
  iota(par.begin(), par.end(), 0); 
  fill(comp.begin(), comp.end(), 1); 
  int64_t cost = 0, cnt = 0, cc = 0; 
  for(auto [w, u, v, s] : edge) { 
   if(merge(u, v)) {
    cost += w; 
    cnt++; 
    cc += s;
   }
  }
  array<int64_t, 3> ret = {cost, cnt, cc}; 
  return ret; 
 }; 
 sort(edge.begin(), edge.end(), [&](array<int, 4> a, array<int, 4> b) { 
  return a[3] == b[3] ? a[0] < b[0] : a[3] < b[3]; 
 }); 
 auto Lb = kruskal(); 
 sort(edge.begin(), edge.end(), [&](array<int, 4> a, array<int, 4> b) { 
  return a[3] == b[3] ? a[0] < b[0] : a[3] > b[3]; 
 }); 
 auto Rb = kruskal(); 
 if(Rb[2] < W || W < Lb[2] || Lb[1] < N - 1) { 
  cout << -1 << '\n'; 
  return 0; 
 }
 auto search = [&](int offset) { 
  int lo = 0, hi = 400000;
  while(lo <= hi) { 
   int mid = (lo + hi + offset) / 2; 
   int d = mid - 200000; 
   sort(edge.begin(), edge.end(), [&](array<int, 4> a, array<int, 4> b) { 
    return a[0] + a[3] * d == b[0] + b[3] * d ? a[3] < b[3] : a[0] + a[3] * d < b[0] + b[3] * d; 
   }); 
   auto Lb1 = kruskal(); 
   sort(edge.begin(), edge.end(), [&](array<int, 4> a, array<int, 4> b) { 
    return a[0] + a[3] * d == b[0] + b[3] * d ? a[3] > b[3]  : a[0] + a[3] * d <  b[0] + b[3] * d; 
   });
   auto Rb1 = kruskal(); 
  //cout << Lb[2] << " " << Rb1[2] << " " << W << " " << mid << " " << d << '\n'; 
   if(Lb1[2] > W) { 
     lo = mid + 1; 
   } else if(W > Rb1[2]) { 
     hi = mid - 1; 
   } else { 
    cout << Lb1[0] - (W -Lb1[2]) * d << '\n'; 
    exit(0); 
   }
  } 
 }; 
 search(0); 
 search(1); 
 //cout << lo << '\n'; 
 return 0; 
}