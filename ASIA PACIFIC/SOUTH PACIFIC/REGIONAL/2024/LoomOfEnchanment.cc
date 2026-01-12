#include "bits/stdc++.h"

using namespace std;  

const int MOD = 1e9 + 7; 

#define ll long long 
#define sz(x) int(x.size()) 

template<typename T> 
struct Fenwick { 
  vector<T>bit; 
  Fenwick(int n) { 
   bit.resize(n + 1, 0); 
  }
  void upd(int idx, T val) { 
   for(idx++; idx < sz(bit); idx += idx & -idx) { 
    bit[idx] += val; 
    bit[idx] %= MOD; 
   }
   return; 
  }
  T query(int idx) { 
   T sum = 0; 
   for(idx++; idx > 0; idx -= idx & -idx) {
    sum += bit[idx]; 
    sum %= MOD; 
   }
   return sum; 
  }
  T query(int l, int r) { 
   return (query(r) - query(l - 1) + MOD) % MOD ; 
  }
  void reset() { 
   fill(bit.begin(), bit.end(), 0); 
  }
}; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n; 
 cin >> n; 
 vector<int>a(n), coord; 
 for(auto &x : a) { 
  cin >> x; 
  coord.push_back(x); 
 }
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
 for(auto &x : a) { 
   x = lower_bound(coord.begin(), coord.end(), x) - coord.begin(); 
 }
 Fenwick<ll>fenw(sz(coord) + 7), fenw_cnt(sz(coord) + 7);
 vector<ll>prefix(n), suffix(n);  
 for(int i = 0; i < n; i++) { 
  prefix[i] += (fenw.query(a[i], n) - fenw_cnt.query(a[i], n) * coord[a[i]] % MOD + MOD);
  prefix[i] %= MOD;   
  prefix[i] += (fenw_cnt.query(0, a[i]) * coord[a[i]] % MOD - fenw.query(0, a[i]) + MOD);
  prefix[i] %= MOD;  
  fenw.upd(a[i], coord[a[i]]); 
  fenw_cnt.upd(a[i], 1); 
 }
 fenw.reset(); 
 fenw_cnt.reset(); 
 for(int i = n - 1; i >= 0; i--) { 
  suffix[i] += (fenw.query(a[i], n) - fenw_cnt.query(a[i], n) * coord[a[i]] % MOD + MOD);
  suffix[i] %= MOD;   
  suffix[i] += (fenw_cnt.query(0, a[i]) * coord[a[i]] % MOD - fenw.query(0, a[i]) + MOD);
  suffix[i] %= MOD;  
  fenw.upd(a[i], coord[a[i]]); 
  fenw_cnt.upd(a[i], 1); 
 }
 ll ans = 0; 
 for(int i = 0; i < n; i++) {
  ans += prefix[i] * suffix[i] % MOD;
  ans %= MOD;  
 }
 cout << ans << '\n'; 
 return 0; 
}