#include <bits/stdc++.h>

using namespace std; 

const int MOD = 998244353; 

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

int main() {
  string s; 
  int N, M; 
  cin >> N >> M >> s;
  int64_t ret = 1, retButFirst = 1;
  for(int i = 0; i < N; i++) { 
    if(s[i] == '?') {
      ret = ret * i % MOD; 
      if(i > 0) retButFirst = retButFirst * i % MOD; 
    } 
  } 
  cout << ret << '\n'; 
  for(int i = 0, pos; i < M; i++) { 
    char c;
    cin >> pos >> c; 
    --pos; 
    if(c == '?') { 
      if(pos == 0) { 
        ret = 0; 
        s[pos] = c; 
      } 
      else { 
        if(s[pos] != c) { 
          ret = ret * pos % MOD; 
          retButFirst = retButFirst * pos % MOD; 
        } 
        s[pos] = c; 
      } 
    }
    else {
      if(pos == 0) { 
        if(s[pos] == '?') { 
          ret = retButFirst; 
        }
      } 
      else { 
        if(s[pos] == '?') { 
          ret = ret % MOD * mod_inv(pos, MOD) % MOD;
          retButFirst = retButFirst % MOD * mod_inv(pos, MOD) % MOD; 
        } 
        s[pos] = c; 
      } 
    }
    cout << ret << '\n'; 
  } 
  return 0; 
}