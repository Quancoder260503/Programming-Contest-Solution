#include "bits/stdc++.h"

using namespace std; 

const int LOG = 20; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N; 
  cin >> N; 
  vector<int64_t>a(N), dp(1 << LOG); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
    int64_t num = 0; 
    for(int j = 0; j < 2 * LOG; j += 2) { 
      if(a[i] & (1LL << j)) { 
        num += (1LL << (j / 2)); 
      }
    }
    a[i] = num;  
    dp[num]++; 
  }
  for(int i = 0; i < LOG; i++) { 
    for(int mask = 0; mask < (1 << LOG); mask++) { 
      if(mask & (1 << i)) { 
        dp[mask] += dp[mask ^ (1 << i)]; 
      }
    }
  }
  int64_t ret = 0;
  for(int i = 0; i < N; i++) { 
    ret += dp[((1 << LOG) - 1) ^ a[i]]; 
    if(a[i] == 0) ret--; 
  } 
  ret = ret / 2; 
  cout << ret << '\n'; 
  return 0; 
}
/*
*/