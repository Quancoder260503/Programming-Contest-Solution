#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 998244353;
const int maxf = 1e5 + 1; 

int N, M; 
vector<int>l, r; 

int64_t knapsack(int g) { 
  vector<vector<int64_t>> ways(N + 1, vector<int64_t>(M / g + 1)); 
  vector<int64_t>prefix(M / g + 1); 
  ways[0][0] = 1; 
  for(int i = 0; i < N; i++) { 
    int minBound = l[i] / g; 
    if(minBound * g < l[i]) minBound++; 
    int maxBound = r[i] / g; 
    if(minBound > maxBound || minBound == 0) continue;
    prefix[0] = ways[i][0]; 
    for(int j = 1; j < sz(ways[i]); j++) { 
      prefix[j] = (prefix[j - 1] + ways[i][j]) % MOD; 
    }
    for(int j = minBound; j < sz(ways[i]); j++) { 
      ways[i + 1][j] = (prefix[j - minBound] - (j > maxBound ? prefix[j - maxBound - 1] : 0) + MOD) % MOD; 
    } 
  }
  int64_t ret = 0; 
  for(int i = 0; i < sz(ways[N]); i++) { 
    (ret += ways[N][i]) %= MOD; 
  }
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> M; 
  l.resize(N); 
  r.resize(N); 
  for(int i = 0; i < N; i++) { 
    cin >> l[i] >> r[i]; 
  }
  vector<int64_t> ways(M + 1); 
  for(int i = 1; i <= M; i++) { 
    ways[i] = knapsack(i); 
  }
  for(int i = M; i > 0; i--) { 
    for(int j = 2 * i; j <= M; j += i) { 
      (ways[i] += MOD - ways[j]) %= MOD; 
    }
  }
  cout << ways[1] << '\n'; 
  return 0; 
}
/*

*/ 