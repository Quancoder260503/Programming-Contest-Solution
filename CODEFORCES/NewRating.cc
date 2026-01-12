#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int oo = 1e9; 


int main(void) {
 ios_base::sync_with_stdio(0); 
 cin.tie(0); 
 cout.tie(0); 
 int T;
 for(cin >> T; T--; ) { 
  int n; 
  cin >> n; 
  vector<int>a(n); 
  for(auto &x : a) { 
   cin >> x; 
  }
  set<int>ms;
  int x = 0; 
  vector<int>dp(n, -oo);  
  vector<int>prefix(n); 
  for(int i = 0; i < n; i++) { 
   if(ms.size()) { 
    if(a[i] < *prev(ms.end())) { 
     dp[i] = *prev(ms.end()) - 1; 
    } else if(a[i] > *prev(ms.end())) { 
     dp[i] = *prev(ms.end()) + 1; 
    } else { 
     dp[i] = *prev(ms.end()); 
    }
    auto it = ms.lower_bound(a[i]); 
    if(it != ms.end() && (*it == a[i])) { 
     dp[i] = max(dp[i], *it); 
    }
    if(it != ms.begin()) { 
     it--; 
     dp[i] = max(dp[i], *it + 1); 
    }
   } 
   x += (x == a[i] ? 0 : (x < a[i] ? 1 : -1)); 
   if(i > 0) { 
    ms.insert(prefix[i - 1]); 
    dp[i] = max(dp[i], a[i] == dp[i - 1] ? dp[i - 1] : (a[i] < dp[i - 1] ? dp[i - 1] - 1 : dp[i - 1] + 1)); 
   } 
   prefix[i] = x; 
  }
  ms.insert(dp[n - 1]); 
  cout << max(0, *prev(ms.end())) << '\n'; 
 }
 return 0; 
}
