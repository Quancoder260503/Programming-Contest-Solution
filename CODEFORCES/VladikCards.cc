#include "bits/stdc++.h"
 
using namespace std;
 
const int oo = 1e9; 
 
int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 int N; 
 cin >> N; 
 vector<int>a(N + 1); 
 vector<vector<int>>prefix(8, vector<int>(N + 1)); 
 for(int i = 1; i <= N; i++) { 
  cin >> a[i];
  --a[i]; 
  prefix[a[i]][i]++; 
  for(int j = 0; j < 8; j++) { 
   prefix[j][i] += prefix[j][i - 1]; 
  }
 }
 auto f = [&](int len, int printme) { 
  vector<vector<int>>dp(N + 1, vector<int>(1 << 8, -oo));
  vector<vector<int>>best(N + 1, vector<int>(1 << 8, -oo)); 
  dp[0][0] = 0;
  for(int mask = 0; mask < (1 << 8); mask++) { 
   for(int col = 0; col < 8; col++) { 
    if(mask & (1 << col)) { 
     for(int pos = 1; pos <= N; pos++) { 
      int bound = prefix[col][pos] - len; 
      auto it = upper_bound(prefix[col].begin(), prefix[col].end(), bound); 
      // (prefix[col][pos] - prefix[col][pre] >= len) -> (bound >= prefix[col][pre])
      if(it != prefix[col].begin()) { 
       --it; 
       int pre = it - prefix[col].begin(); 
       dp[pos][mask] = max(dp[pos][mask], len + best[pre][mask ^ (1 << col)]);  
      }
      it = upper_bound(prefix[col].begin(), prefix[col].end(), bound - 1); 
      if(it != prefix[col].begin()) { 
       --it; 
       int pre = it - prefix[col].begin(); 
       dp[pos][mask] = max(dp[pos][mask], (len + 1) + best[pre][mask ^ (1 << col)]);  
      }
     } 
    }
   }
   best[0][mask] = dp[0][mask]; 
   for(int i = 1; i <= N; i++) { 
     best[i][mask] = max(best[i - 1][mask], dp[i][mask]); 
   //  if(mask == 1) cout << best[i][mask] << " " << dp[i][mask] << '\n'; 
   }
  }
  int ret = -oo; 
  for(int i = 0; i <= N; i++) { 
   ret = max(ret, dp[i][(1 << 8) - 1]); 
   if(len == 0) { 
    for(int mask = 0; mask < (1 << 8); mask++) { 
      ret = max(ret, dp[i][mask]); 
    } 
   }
  }
  if(printme) { 
   cout << ret << '\n'; 
  }
  return ret >= 0; 
 }; 
 int lo = 0, hi = N; 
 while(lo < hi) { 
  int mid = (lo + hi + 1) / 2; 
  if(f(mid, 0)) { 
   lo = mid; 
  } else { 
    hi = mid - 1; 
  }
 }
 f(lo, 1); 
 return 0; 
}

