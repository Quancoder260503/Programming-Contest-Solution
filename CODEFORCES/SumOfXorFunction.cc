#include <bits/stdc++.h>

using namespace std;

#define sz(x) int(x.size())

const int LOG = 31; 
const int MOD = 998244353; 


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N; 
  cin >> N; 
  vector<int>a(N + 1); 
  for(int i = 1; i <= N; i++) { 
   cin >> a[i]; 
  } 
  int64_t ans = 0; 
  for(int mask = 0; mask < LOG; mask++) { 
   int acc = 0; 
   int64_t sum0 = 0, sum1 = 0, num0 = 1, num1 = 0, ret = 0; 
   for(int i = 1; i <= N; i++) { 
    acc = acc ^ a[i]; 
    if(acc & (1 << mask)) {
     (ret += 1LL * num0 % MOD * i % MOD - sum0 + MOD) %= MOD; 
     num1++; 
     (sum1 += i) %= MOD; 
    }
    else { 
     (ret += 1LL * num1 % MOD * i % MOD - sum1 + MOD) %= MOD; 
     num0++; 
     (sum0 += i) %= MOD; 
    } 
   }
   //if(ret) cout << sum << " " << num << " " << ret << '\n'; 
   ans += (1 << mask) % MOD * ret % MOD; 
   ans %= MOD;
  } 
  cout << ans << '\n'; 
  return 0;
}
