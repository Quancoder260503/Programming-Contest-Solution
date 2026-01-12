#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, M;
  cin >> N >> M; 
  string p;  
  vector<string>s; 
  for(int i = 0; i < M; i++) { 
   cin >> p; 
   int good = true; 
   vector<int>cc(26, 0); 
   for(int j = 0; j < sz(p); j++) { 
    if(p[j] - 'A' >= N) { good = false; break; }
    cc[p[j] - 'A']++; 
    if(cc[p[j] - 'A'] > 1) { 
     good = false; 
     break; 
    }
   }
   if(good) { 
    s.push_back(p); 
   } 
  }
  M = sz(s); 
  vector<int>c(M, 0);
  for(int i = 0; i < M; i++) { 
   for(int j = 0; j < sz(s[i]); j++) {  
    c[i] |= 1 << (s[i][j] - 'A'); 
   }  
  }
  vector<int>word(1 << M), dp(1 << M, -1); 
  for(int mask = 0; mask < (1 << M); mask++) { 
   for(int i = 0; i < M; i++) { 
    word[mask] |= (mask >> i & 1) * c[i]; 
   } 
  }
  dp[0] = 0; 
  for(int mask = 0; mask < (1 << M); mask++) { 
   if(dp[mask] == -1) continue;
   for(int i = 0; i < M; i++) { 
    if(mask >> i & 1 || (c[i] & word[mask]) > 0) continue;
    dp[mask ^ (1 << i)] = max(dp[mask ^ (1 << i)], dp[mask] + 1); 
   }
  }
  int ans = 0; 
  for(int i = 0; i < (1 << M); i++) { 
   if(dp[i] == -1) continue;
   ans = max(ans, dp[i]); 
   //cout << i << " " << dp[i] << '\n'; 
  }
  cout << ans << '\n'; 
  return 0;
}