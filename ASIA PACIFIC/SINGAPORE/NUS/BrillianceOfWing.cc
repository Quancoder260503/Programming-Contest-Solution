#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int maxn = 1e5 + 2; 
set<int>g_a[maxn], g_b[maxn]; 

int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int n; 
  cin >> n; 
  for(int i = 0, u, v; i < n - 1; i++) { 
   cin >> u >> v; 
   if(u > v) swap(u, v); 
   g_a[u].insert(v); 
  }
  for(int i = 0, u, v; i < n - 1; i++) { 
   cin >> u >> v; 
   if(u > v) swap(u, v); 
   g_b[u].insert(v); 
  }
  int ret = 0; 
  for(int i = 1; i <= n; i++) { 
   for(auto v : g_b[i]) { 
    ret += !g_a[i].count(v); 
   }
  }
  cout << ret << '\n'; 
  return 0; 
}
