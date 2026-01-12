#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxn = 1e7 + 2; 

int64_t suffix[maxn]; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int n, T; 
  for(cin >> T; T--; ) { 
   cin >> n; 
   vector<int>a(n), coord; 
   for(auto &x : a) { 
    cin >> x; 
   } 
   for(int i = 0; i < n; i++) { 
    for(int j = i + 1; j < n; j++) { 
     suffix[a[i] * n + a[j]]++; 
    }
   }
   int64_t ans = 0; 
   for(int i = 0; i < n; i++) { 
    for(int j = i + 1; j < n; j++) { 
     suffix[a[i] * n + a[j]]--; 
    }
    for(int j = 0; j < i; j++) { 
     ans += suffix[a[j] * n + a[i]]; 
    }
   }
   cout << ans << '\n'; 
   for(int i = 0; i < n; i++) { 
    for(int j = 0; j < i; j++) { 
     suffix[a[j] * n + a[i]] = 0; 
    }
   }
  } 
  return 0; 
}
