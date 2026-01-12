#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;
const int maxn = 1e6 + 10;

int64_t fact[maxn], ifact[maxn];

int64_t Comb(int n, int k) {
  if (n < k || k < 0) return 0;
  return fact[n] % MOD * ifact[n - k] % MOD * ifact[k] % MOD;
}

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

int64_t f(const string &s) {
  int64_t ret = 0;
  int num_68 = 0, num_other = 0;
  int i; 
  for(int j = 0; j < sz(s); j++) { 
   int rem = sz(s) - 1 - j; 
   if(rem % 2 == 0) { 
    ret += 6LL * mod_pow(7, rem / 2 - 1, MOD) % MOD * mod_pow(2, rem / 2, MOD) % MOD * Comb(rem - 1, rem / 2) % MOD; 
    ret += 2LL * mod_pow(7, rem / 2, MOD) % MOD * mod_pow(2, rem / 2 - 1, MOD) % MOD * Comb(rem - 1, rem / 2) % MOD; 
    ret %= MOD; 
   } 
  }
  for (i = 0; i < sz(s); i++) {
    int rem = sz(s) - 1 - i; 
    for (int d = (i == 0); d < (s[i] - '0'); d++) {
      if (d == 4) continue;
      int nxt_num68 = num_68; 
      int nxt_numother = num_other; 
      if (d == 6 || d == 8) {
        nxt_num68++; 
      } else { 
        nxt_numother++; 
      }
      if (nxt_num68 >= nxt_numother) {
        int dist = nxt_num68 - nxt_numother; 
        if ((rem - dist) & 1) continue;
        ret += mod_pow(7, dist, MOD) % MOD * mod_pow(2, (rem - dist) / 2, MOD) % MOD *
               mod_pow(7, (rem - dist) / 2, MOD) % MOD * Comb(rem, dist + (rem - dist) / 2) % MOD *
               Comb(rem - dist - (rem - dist) / 2, (rem - dist) / 2) % MOD;
        ret %= MOD;
      } else {
        int dist = nxt_numother - nxt_num68; 
        if ((rem - dist) & 1) continue;
        ret += mod_pow(2, dist, MOD) % MOD * mod_pow(2, (rem - dist) / 2, MOD) % MOD *
               mod_pow(7, (rem - dist) / 2, MOD) % MOD * Comb(rem, dist + (rem - dist) / 2) % MOD *
               Comb(rem - dist - (rem - dist) / 2, (rem - dist) / 2) % MOD;
        ret %= MOD;
      }
    }
    num_68 += (s[i] == '6' || s[i] == '8');
    num_other += (s[i] != '6' && s[i] != '8');
    if (s[i] == '4') break;
  }
  ret += (i == sz(s) && (num_68 == num_other)); 
  return ret;
}

int check(const string &s) { 
 int num_68 = 0, num_other = 0, no_four = true;
 for(int i = 0; i < sz(s); i++) {
  if(s[i] == '4') {
   no_four = false;
   break;
  }
  num_68    += (s[i] == '6' || s[i] == '8');
  num_other += (s[i] != '6' && s[i] != '8');
 }
 return (no_four && (num_68 == num_other));
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxn; i++) {
    fact[i] = fact[i - 1] * i % MOD;
    ifact[i] = mod_inv(fact[i], MOD);
  }
  string L, R;
  cin >> L >> R;
  int64_t ret = (f(R) - f(L) + MOD) % MOD;
  int num_68 = 0, num_other = 0, no_four = true;
  for(int i = 0; i < sz(L); i++) {
   if(L[i] == '4') {
    no_four = false;
    break;
   }
   num_68    += (L[i] == '6' || L[i] == '8');
   num_other += (L[i] != '6' && L[i] != '8');
  }
  ret += (no_four && (num_68 == num_other));
  cout << ret << '\n';
  return 0;
}