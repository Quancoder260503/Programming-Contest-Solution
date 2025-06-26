#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long
const int mod = 998244353;
const int maxf = 3e5 + 2;

int64_t Prob[maxf], a[2][maxf]; 
set<int>checkPoint; 
int N, Q; 

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
} 

int64_t den(int lo, int hi) { 
   int64_t ret = a[1][hi] % mod * fpow(a[1][lo - 1], mod - 2) % mod; 
   return fpow(ret, mod - 2); 
}

int64_t num(int lo, int hi) { 
  return (1 + (a[0][hi] - a[0][lo - 1] + mod) % mod * fpow(a[1][lo - 1], mod - 2) % mod); 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> Q;
  checkPoint.insert(1); 
  int64_t acc = 1; 
  for(int i = 1; i <= N; i++) { 
    cin >> Prob[i]; 
    Prob[i] = Prob[i] % mod * fpow(100, mod - 2) % mod; 
    acc = acc % mod * Prob[i] % mod; 
    a[0][i] = (a[0][i - 1] + acc) % mod; 
  }
  acc = a[1][0] = 1; 
  for(int i = 1; i <= N; i++) {
    acc = acc % mod * Prob[i] % mod; 
    a[1][i] = acc; 
  } 
  int64_t ret = ((1 + a[0][N]) % mod * fpow(a[1][N], mod - 2) % mod - 1 + mod) % mod;
  for(int i = 0, pos; i < Q; i++) { 
    cin >> pos; 
    if(checkPoint.count(pos)) { 
      checkPoint.erase(pos); 
      auto it = checkPoint.lower_bound(pos); 
      int lo, hi; 
      if(it != checkPoint.end()) { hi = *it, lo = *(--it); }
      else { it--; lo = (*it), hi = N + 1; }
      (ret += num(lo, hi - 1) % mod * den(lo, hi - 1) % mod - 1 + mod)          %= mod; 
      (ret += mod - num(lo, pos - 1) % mod * den(lo, pos - 1) % mod + 1) %= mod; 
      (ret += mod - num(pos, hi - 1) % mod * den(pos, hi - 1) % mod + 1) %= mod; 
    }
    else {  
      auto it = checkPoint.lower_bound(pos); 
      int lo, hi; 
      if(it != checkPoint.end()) { hi = *it, lo = *(--it); }
      else { it--; lo = (*it), hi = N + 1; }    
      (ret += mod - num(lo, hi - 1) % mod * den(lo, hi - 1) % mod + 1)      %= mod; 
      (ret += num(lo, pos - 1) % mod * den(lo, pos - 1) % mod - 1 + mod) %= mod; 
      (ret += num(pos, hi - 1) % mod * den(pos, hi - 1) % mod - 1 + mod) %= mod; 
      checkPoint.insert(pos);
    }
    cout << ret << '\n'; 
  }
  return 0; 
}