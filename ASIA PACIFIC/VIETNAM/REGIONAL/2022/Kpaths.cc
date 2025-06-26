#include "bits/stdc++.h"
 
using namespace std; 

const int64_t oo = 1e12; 
const int MAXN = 2e5 + 10;

vector<int>g[MAXN]; 
int N, K; 
int64_t a[MAXN]; 

pair<int64_t, int>dfs(int u, int p, int64_t thres) {  
  pair<int64_t, int64_t>opt = make_pair(a[u], oo); 
  int cnt_pair = 0; 
  for(auto v : g[u]) { 
   if(v == p) continue; 
   auto [up, cnt] = dfs(v, u, thres); 
   cnt_pair += cnt; 
   if(up < opt.first) {
    opt.second = opt.first;  
    opt.first = up;  
   } else if(up < opt.second) { 
    opt.second = up; 
   }
  }
  if(opt.first + opt.second <= thres) { 
   return make_pair(oo, cnt_pair + 1); 
  }
  return make_pair(opt.first, cnt_pair); 
} 
int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> N >> K; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 for(int i = 0, u, v; i < N - 1; i++) { 
  cin >> u >> v; 
  --u, --v; 
  g[u].push_back(v); 
  g[v].push_back(u); 
 }
 auto check = [&](int64_t c) { 
  pair<int64_t, int>ans = dfs(0, -1, c); 
  return ans.second >= K; 
 }; 
 int cc = 0; 
 int64_t lo = 0, hi = 2LL * oo + 2; 
 while(lo < hi) { 
  int64_t mid = (lo + hi) / 2;
  if(check(mid)) hi = mid; 
  else lo = mid + 1; 
 }
 cout << (lo >= oo ? -1 : lo)  << '\n'; 
 return 0; 
}
