#include "bits/stdc++.h"

using namespace std;

const int MOD = 998244353;
const int OFFSET = 3005; 

class ObsecureString {
public:
 void solve() {
  int N;
  string S;
  cin >> N >> S;
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(OFFSET * 2, -1)); 
  int64_t inv2 = mod_inv(2, MOD);
  // diff = end_0 - end_1
  function<int64_t(int, int)> memo = [&](int pos, int diff) -> int64_t {
   if (pos == N) return 0;
   int64_t &ret = dp[pos][diff + OFFSET];
   if (ret != -1) return ret;
   ret = 0;
   if (S[pos] == '0') {
    ret += (diff >= 0) + memo(pos + 1, diff + 1);
   } else if (S[pos] == '1') {
    ret += 1 + memo(pos + 1, diff >= 0 ? -1 : diff - 1);
   } else {
    ret += ((diff >= 0) + memo(pos + 1, diff + 1) +
            1 + memo(pos + 1, diff >= 0 ? -1 : diff - 1)) % MOD * inv2 % MOD;
   }
   ret %= MOD;
   return ret;
  };
  cout << (N - memo(0, 0) + MOD) % MOD << '\n'; 
 }

private:
 int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
   if (b & 1) res = (res * a) % p;
   a = (a * a) % p;
   b >>= 1;
  }
  return res;
 }
 int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }
}; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 ObsecureString task; 
 task.solve(); 
 return 0;
}
