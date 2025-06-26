#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7; 

int64_t nums(int x) { 
  return 1 + (x == 0 ? 0LL : (1LL * x % mod * nums(x - 1) % mod)); 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  vector<int64_t>a(1 << M), ways(1 << M); 
  vector<vector<char>>g(M, vector<char>(N)); 
  for(int i = 0; i < M; i++) { 
    for(int j = 0; j < N; j++) {
      cin >> g[i][j]; 
    }
  }
  for(int i = 0; i < N; i++) { 
    int hardSet = 0; 
    for(int j = 0; j < M; j++) { 
      hardSet |= (g[j][i] == 'H') * (1 << j); 
    }
    a[hardSet]++;
  }
  int64_t ret = 0; 
  vector<vector<int64_t>>dyn((1 << M), vector<int64_t>(M));
  for(int mask = 0; mask < (1 << M); mask++) { 
    int64_t sum = 1; 
    for(int i = 0; i < M; i++) { 
      if(mask & (1 << i)) { 
        (sum += dyn[mask ^ (1 << i)][i]) %= mod; 
      }
    }
    ways[mask] = sum % mod * (nums(a[mask]) - 1) % mod;
    (ret += ways[mask]) %= mod; 
    dyn[mask][0] = ways[mask]; 
    for(int i = 0; i < M - 1; i++) { 
      dyn[mask][i + 1] = dyn[mask][i]; 
      if(mask & (1 << i)) { 
        (dyn[mask][i + 1] += dyn[mask ^ (1 << i)][i]) %= mod; 
      }
    }  
  }
  cout << ret << '\n'; 
  return 0; 
}

/*
*/
