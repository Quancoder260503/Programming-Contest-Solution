#include "bits/stdc++.h"

using namespace std;


const double eps = 1e-5;
const double oo = 1e30; 
const int maxf = 2510; 


int K, N; 
double dyn[maxf][maxf]; 
vector<int>productivity, salary, tree_sz, sz; 
vector<vector<int>>g; 

void doit(int u) { 
  sz[u] = 1; 
  for(auto v : g[u]) { 
    doit(v); 
    sz[u] += sz[v]; 
  }
  return; 
}

void dfs(int u, double x) {
  fill(dyn[u], dyn[u] + min(K, sz[u]) + 1, -oo); 
  tree_sz[u] = 1;  
  if(u) dyn[u][1] = 1.0 * productivity[u] - x * salary[u];
  else dyn[u][0] = 0; 
  for(auto v : g[u]) { 
    dfs(v, x); 
    for(int weight = min(K, tree_sz[u]); weight >= 0; weight--) { 
      for(int c_weight = 0; c_weight <= min(tree_sz[v], K) && 
                            c_weight + weight <= min(K, sz[u]); c_weight++) { 
        dyn[u][weight + c_weight] = max(dyn[u][weight + c_weight], 
                                        dyn[u][weight] + dyn[v][c_weight]); 
      }
    }
    tree_sz[u] += tree_sz[v]; 
  }
}

double f(double x) { 
  dfs(0, x); 
  return (dyn[0][K] >= 0); 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> K >> N; 
  g.resize(N + 1);
  productivity.resize(N + 1); 
  salary.resize(N + 1); 
  tree_sz.resize(N + 1); 
  sz.resize(N + 1); 
  for(int i = 1, voter; i <= N; i++) { 
    cin >> salary[i] >> productivity[i] >> voter;
    g[voter].push_back(i); 
  }
  doit(0); 
  double lo = 0, hi = 10000; 
  for(int iter = 0; iter < 40; iter++) { 
    double mid = (lo + hi) / 2; 
    if(f(mid)) { lo = mid; }
    else { hi = mid; }
  }
  cout << fixed << setprecision(3) << lo << '\n';  
  return 0; 
}
/*
  P(i[1]) + P(i[2]) + ... + P(i[k]) 
  --------------------------------  >= THRES
  S(i[1]) + S(i[2]) + ... + S(i[k])

  Sum(P(i[j]) - THRES * S(i[j])) >= 0
*/ 