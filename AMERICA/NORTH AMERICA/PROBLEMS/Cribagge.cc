#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);   
  int N; 
  cin >> N; 
  vector<vector<int64_t>>dyn(N + 1, vector<int64_t>(16));
  vector<int>counter(14); 
  vector<int>a(N + 1); 
  dyn[0][0] = 1; 
  int64_t ret = 0;
  string rank = "ATJQK";  
  for(int i = 1; i <= N; i++) { 
    char c; 
    cin >> c; 
    if(rank.find(c) == -1) { 
      a[i] = c - '0'; 
    } else if(rank.find(c) == 0) {
      a[i] = 1;  
    } else { 
      a[i] = rank.find(c) + 9; 
    }
    for(int j = 0; j < 16; j++) {
      dyn[i][j] += dyn[i - 1][j];  
      if(j >= min(10, a[i])) dyn[i][j] += dyn[i - 1][j - min(10, a[i])]; 
    }
    counter[a[i]]++; 
  }
  ret += dyn[N][15] * 2; 
  for(int i = 1; i < 14; i++) { 
    ret += 1LL * counter[i] * (counter[i] - 1); 
  }
  for(int i = 1; i < 14; i++) { 
    if(counter[i] > 0) { 
      int64_t ways = counter[i]; 
      int len = 1; 
      while(counter[i + 1] > 0 && i + 1 < 14) { i++; ways = 1LL * ways * counter[i]; len++; }
      if(len >= 3) ret += 1LL * ways * len; 
    }
  }
  cout << ret << '\n'; 
  return 0; 
}