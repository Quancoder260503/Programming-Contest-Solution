#include "bits/stdc++.h"

using namespace std; 

#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int mod = 1e9 + 7;
const int LOG = 20; 

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

int64_t dyn[1 << LOG][LOG], Prob[3][LOG][LOG]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, M; 
  cin >> N >> M;
  int64_t den = fpow(1000000, mod - 2); 
  for(int k = 0; k < 3; k++) { 
    for(int j = 0; j < M; j++) {
      for(int i = 0; i < N; i++) { 
        cin >> Prob[k][i][j]; 
        Prob[k][i][j] = Prob[k][i][j] % mod * den % mod; 
      }
    }
  }
  int64_t ret = 0, last = 0;
  for(int step = 1; step <= 3 * M; step++) {
    for(int mask = 0; mask < (1 << M); mask++) { 
      for(int i = 0; i <= step; i++) { 
        dyn[mask][i] = 0; 
      }
    }
    dyn[0][0] = 1; 
    for(int i = 0; i < N; i++) {
      for(int task = 0; task < M; task++) { 
        for(int pos = 1; pos <= 3; pos++) { 
          for(int j = 0; j + pos <= step; j++) { 
            for(int mask = 0; mask < (1 << M); mask++) { 
              if(mask & (1 << task)) { 
                (dyn[mask][j + pos] += dyn[mask ^ (1 << task)][j] % mod * Prob[pos - 1][i][task] % mod) %= mod;   
              }        
            }
          }       
        }
      }
      for(int mask = 0; mask < (1 << M); mask++) { 
        for(int j = 1; j <= step; j++) { 
          (dyn[mask][0] += dyn[mask][j]) %= mod; 
          dyn[mask][j] = 0; 
        }
      }
    }
    (ret += (dyn[(1 << M) - 1][0] - last + mod) % mod * step % mod) %= mod; 
    last = dyn[(1 << M) - 1][0]; 
  }
  cout << ret << '\n'; 
  return 0; 
}

/*
*/ 