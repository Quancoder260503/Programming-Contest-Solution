#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 1e6 + 2; 
map<string, int>g[maxf]; 
int cost[maxf], depth[maxf]; 
int N, M; 

void doit(int u) { 
  for(const auto &[str, v] : g[u]) { 
    depth[v] = depth[u] + 1; 
    doit(v); 
    cost[u] += cost[v]; 
  }
  return; 
}

int doit2(int u, int cur_cost) { 
  int ret = cur_cost; 
  for(const auto &[str, v] : g[u]) { 
    int a_cost = cur_cost + N - 2 * cost[v]; 
    if(a_cost < cur_cost && sz(g[v])) { 
      ret = min(ret, doit2(v, a_cost)); 
    }
  }
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N; 
  M = 1; 
  for(int i = 0; i < N; i++) { 
    string S;
    cin >> S; 
    int cc = 0; 
    for(int j = 1, k = 1; j < sz(S); j = k + 1, k++) { 
      string cword; 
      while(k < sz(S) && S[k] != '/') k++; 
      cword = S.substr(j, k - j); 
      if(g[cc].count(cword) == 0) g[cc][cword] = M++;
      cc = g[cc][cword];  
    }
    cost[cc]++; 
  }
  doit(0); 
  int cur_cost = 0; 
  for(int i = 0; i < M; i++) { 
    if(sz(g[i])) continue; 
    cur_cost += depth[i] * cost[i];
  }
  cout << doit2(0, cur_cost) << '\n'; 
  return 0; 
}