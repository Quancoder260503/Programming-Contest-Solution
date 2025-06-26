#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;
const int maxf = 1e6 + 10;

int64_t fact[maxf], ifact[maxf]; 

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % MOD * tmp % MOD;
    }
    tmp = (int64_t)tmp % MOD * tmp % MOD;
    k >>= 1;
  }
  return res;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % MOD * i % MOD;
  }
  ifact[maxf - 1] = fpow(fact[maxf - 1], MOD - 2); 
  for(int i = maxf - 2; i >= 0; i--) { 
    ifact[i] = ifact[i + 1] % MOD * (i + 1) % MOD; 
  }
  return;
}

int N;
string a, b, x;
int cnt[26];

int64_t func() {
  int64_t ret = 0;
  for (int i = 0; i < N; i++) {
    int64_t acc = fact[N - i - 1];
    for (int c = 0; c < 26; c++) {
     acc = acc % MOD * ifact[cnt[c]] % MOD;
    }
    for (char j = 'a'; j < x[i]; j++) {
      if (cnt[j - 'a'] == 0) continue;
      (ret += acc % MOD * cnt[j - 'a'] % MOD) %= MOD;
    }
    if (cnt[x[i] - 'a'] == 0) {
      break;
    } else {
      cnt[x[i] - 'a']--;
    }
  }
  return ret;
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init();
  cin >> a >> b;
  N = sz(a);
  for (int i = 0; i < N; i++) {
    cnt[a[i] - 'a']++;
  }
  x = b;
  int64_t ret = func();
  fill(cnt, cnt + 26, 0);
  for (int i = 0; i < N; i++) {
    cnt[a[i] - 'a']++;
  }
  x = a; 
  (ret += MOD - func()) %= MOD;
  ret--;
  cout << ret << '\n';
  return 0;
}