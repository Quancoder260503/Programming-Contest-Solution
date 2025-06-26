#include "bits/stdc++.h"

using namespace std; 


#define sz(x) int(x.size())
const int maxf = 3e5 + 2; 

vector<int>g[maxf]; 
multiset<int>ms[maxf]; 
int N, a[maxf];  

void dfs(int u, int p) {
  for(auto v : g[u]) { 
    if(v == p) continue; 
    dfs(v, u); 
    if(sz(ms[u]) < sz(ms[v])) swap(ms[u], ms[v]); 
    for(auto &x : ms[v]) { 
      ms[u].insert(x); 
    }
  }
  auto it = ms[u].lower_bound(a[u]); 
  if(it != ms[u].end()) { 
    ms[u].erase(it);  
  }
  ms[u].insert(a[u]);
  return;   
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N; 
  for(int i = 1, u, p; i <= N; i++) { 
    cin >> a[i] >> p; 
    g[p].push_back(i);
  }
  dfs(1, 0); 
  cout << sz(ms[1]) << '\n'; 
  return 0; 
}
