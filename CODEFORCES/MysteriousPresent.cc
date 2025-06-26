#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<array<int, 3>>env; 
  for(int i = 0; i < N + 1; i++) { 
   int w, h; 
   cin >> w >> h; 
   env.push_back({w, h, i}); 
  }
  sort(env.begin() + 1, env.end(), [&](array<int, 3>a, array<int, 3>b) { 
   return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0]; 
  }); 
  vector<int>dp(N + 1, -1), fa(N + 1, -1);
  dp[0] = 0;  
  for(int i = 1; i <= N; i++) { 
   for(int j = 0; j < i; j++) { 
    if(dp[j] == -1) continue; 
    if(env[i][0] > env[j][0] && env[i][1] > env[j][1]) { 
     if(dp[i] < dp[j] + 1) { 
      dp[i] = dp[j] + 1; 
      fa[i] = j; 
     }
    }
   }
  }
  int opt = *max_element(dp.begin(), dp.end()); 
  int st; 
  for(st = 0; st <= N; st++) { 
   if(dp[st] == opt) { break; }
  }
  vector<int>ret; 
  while(st) { 
   ret.push_back(env[st][2]); 
   st = fa[st]; 
  }
  reverse(ret.begin(), ret.end()); 
  cout << opt << '\n'; 
  for(auto &x : ret) cout << x << " "; 
  return 0; 
}