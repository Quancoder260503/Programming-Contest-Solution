#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int64_t oo = LLONG_MAX / 2; 
const int maxf = 1005; 

vector<int>g[maxf]; 
int N, M, C; 
int dyn[maxf][maxf], a[maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> M >> C; 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  for(int i = 0, u, v; i < M; i++) { 
    cin >> u >> v; 
    --u, --v; 
    g[v].push_back(u); 
  }
  memset(dyn, -1, sizeof(dyn)); 
  dyn[0][0] = 0; 
  for(int i = 1; i < maxf; i++) { 
    for(int u = 0; u < N; u++) { 
      for(auto v : g[u]) { 
        if(dyn[v][i - 1] == -1) continue; 
        dyn[u][i] = max(dyn[u][i], dyn[v][i - 1] + a[u]); 
      }
    }
  }
  int64_t ret = -oo; 
  for(int i = 0; i < maxf; i++) { 
    ret = max(ret, dyn[0][i] - 1LL * C * i * i); 
  }
  cout << ret << '\n'; 
  return 0; 
}
