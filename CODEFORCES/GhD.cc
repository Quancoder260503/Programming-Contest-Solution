#include "bits/stdc++.h"

using namespace std; 

#define ll long long 
#define sz(x) int(x.size())


mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n; 
  cin >> n; 
  vector<ll>a(n); 
  for(auto &x : a) cin >> x; 
  // Let the answer be k, then each element in the array has the odd of 0.5 to be divisible by n 
  int S = 15; 
  ll ans = 0; 
  for(int s = 0; s < S; s++) { 
   ll c = a[rng() % n]; 
   vector<ll>cc;
   for(int x = 1; 1LL * x * x <= c; x++) {
    if(c % x == 0) { 
     cc.push_back(x); 
     if(c != 1LL * x * x) cc.push_back(c / x);    
    }
   }
   sort(cc.begin(), cc.end()); 
   vector<int>cnt(cc.size(), 0); 
   for(auto &x : a) {  
    cnt[lower_bound(cc.begin(), cc.end(), gcd(c, x)) - cc.begin()]++; 
   }
   for(int i = 0; i < sz(cc); i++) { 
    for(int j = 0; j < i; j++) {
   //  cerr << cc[i] << " " << cc[j] << '\n';  
     if(cc[i] % cc[j] == 0) cnt[j] += cnt[i];    
    }
   }
   for(int i = 0; i < sz(cc); i++) {
    if(cnt[i] * 2 >= n) ans = max(ans, cc[i]); 
   }
  // cerr << c << '\n'; 
  }
  cout << ans << '\n'; 
  return 0; 
}