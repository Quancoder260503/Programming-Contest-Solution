#include "bits/stdc++.h"

using namespace std; 

#define ll long long 
#define sz(x) int(x.size())

const int L = 100; 

const ll oo = 1e18; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 for(cin >> T; T--; ) { 
  int n; 
  cin >> n; 
  vector<ll>a(n), c(n); 
  for(int i = 0; i < n; i++) { 
   cin >> a[i];   
  }
  for(int i = 0; i < n; i++) { 
   cin >> c[i]; 
  } 
  vector<int>ord(n); 
  iota(ord.begin(), ord.end(), 0); 
  sort(ord.begin(), ord.end(), [&](int x, int y) { 
   return a[x] == a[y] ? c[x] > c[y] : a[x] < a[y];   
  }); 
  vector<ll>prefix(n), prefix_ac(n); 
  for(int i = 0; i < n; i++) { 
   prefix_ac[i] = (i ? prefix_ac[i - 1] : 0) + 1LL * c[ord[i]] * a[ord[i]];
   prefix[i] = (i ? prefix[i - 1] : 0) + c[ord[i]];  
  }
  if(prefix.back() < 0) { 
   cout << "-inf\n"; 
   continue;
  }
  ll ans = oo; 
  ans = min(ans, prefix_ac.back() - 1LL * a[ord[0]] * prefix.back()); 
 // ans = min(ans, prefix_ac.back() + 1LL * oo * prefix.back());
  ans = min(ans, a[ord.back()] * 1LL * prefix.back() - prefix_ac.back());
 // ans = min(ans, oo * prefix.back() - prefix_ac.back()); 
  for(int i = 0; i + 1 < n; i++) { 
   ll weight = prefix[i] * 2 - prefix.back(); 
   ll bias   = prefix_ac.back() - prefix_ac[i]  * 2; 
   ans = min(ans, 1LL * a[ord[i]]     * weight + bias); 
   ans = min(ans, 1LL * a[ord[i + 1]] * weight + bias);  
  }
  cout << ans << '\n'; 
 }
 return 0; 
}

/**
 * The trick is divide into range 
 */