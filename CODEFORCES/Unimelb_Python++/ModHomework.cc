#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int MOD = 1e9 + 7;  
 
struct FT {
  int N;
  vector<int64_t> bit;
  FT(int _N) {
    N = _N;
    bit.resize(N);
  }
  int64_t query(int i) {
    int64_t c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = (c + bit[i]) % MOD;
    }
    return c;
  }
  void update(int i, int64_t dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = (dif + bit[i]) % MOD;
    }
  }
};
 
int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  int m = 998244353; 
  vector<int64_t>a(N), b(N); 
  vector<int>coord; 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
   b[i] = (a[i] + (i ? b[i - 1] : 0)) % m; 
   coord.push_back(b[i]); 
  } 
  coord.push_back(0);  
  sort(coord.begin(), coord.end()); 
  coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
  for(int i = 0; i < N; i++) { 
   a[i] = lower_bound(coord.begin(), coord.end(), b[i]) - coord.begin() + 1; 
  } 
  FT fenw(N + 7), fenw_cnt(N + 7), fenw2(N + 7); 
  int64_t ans = 0;
  fenw_cnt.update(0, 1);
  for(int i = 0; i < N; i++) {  
   int64_t lower = fenw.query(a[i]);
   int64_t upper = (fenw2.query(N + 1) - fenw2.query(a[i]) + MOD) % MOD; 
   int num_lower = fenw_cnt.query(a[i]);
   
   (ans += 1LL * b[i] % MOD * num_lower % MOD - lower + MOD) %= MOD;
   (ans += 1LL * b[i] % MOD * (i + 1 - num_lower) % MOD + upper + MOD) %= MOD; 
   fenw.update(a[i], b[i]);
   fenw2.update(a[i], m - b[i]); 
   fenw_cnt.update(a[i], 1); 
  //cout << ans << " " << b[i] << " " << upper << " " << (m - b[i]) * (i + 1 - num_lower) << '\n'; 
  } 
  cout << ans << '\n';
  return 0; 
} 