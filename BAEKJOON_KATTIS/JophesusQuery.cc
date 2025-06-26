#include "bits/stdc++.h"

using namespace std; 

map<pair<int, int>, int>memo; 

int f(int N, int K) { 
  if(memo.count({N, K})) return memo[{N, K}]; 
  if(N == 1) return memo[{N, K}] = 1; 
  if(2 * K <= N) return memo[{N, K}] = 2 * K;
  if(N & 1) { 
    memo[{N, K}] = (2 * f(N / 2 + (N & 1), K - N / 2) + N - 2) % (N + 1); 
  } 
  else { 
    memo[{N, K}] = 2 * f(N / 2 + (N & 1), K - N / 2) - 1;
  }
  return memo[{N, K}]; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Q; 
  cin >> Q; 
  for(int iter = 0, N, K; iter < Q; iter++) { 
    cin >> N >> K; 
    cout << f(N, K) << '\n'; 
  }
  return 0; 
}

