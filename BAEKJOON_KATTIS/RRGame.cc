#include "bits/stdc++.h"

using namespace std;

const int LOG = 31;
const int MOD = 1e9 + 7; 

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

int64_t Comb(int a, int b) {
#define COMB_MAXA LOG + 10
#define COMB_MAXB LOG + 10
  static int64_t combmemo[COMB_MAXA + 1][COMB_MAXB + 1];
  if (a < b || b < 0) return 0;
  if (!a) return 1;
  int64_t &ret = combmemo[a][b];
  if (!ret) ret = (Comb(a - 1, b - 1) + Comb(a - 1, b)) % MOD;
  return ret;
}

int64_t f(int64_t x) {
  int64_t ret = 0, ones = 0;
  for (int i = LOG; i >= 0; i--) {
   if (x & (1LL << i)) {
    for (int choose = 0; choose <= i; choose++) {
     ret += 1LL * Comb(i, choose) % MOD * (choose + ones) % MOD;
     ret %= MOD; 
    }
    ones++;
   }
  }
  ret += ones;
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int64_t a, b;
  cin >> a >> b;
  cout << (f(b) - f(a - 1) + MOD) % MOD * mod_inv(b - a + 1, MOD) % MOD << '\n';
  return 0;
}