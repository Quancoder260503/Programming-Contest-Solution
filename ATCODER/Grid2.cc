#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int mod = 1e9 + 7;
const int maxf = 3e5 + 10;

int64_t fact[maxf], ifact[maxf];

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

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

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init(); 
  int H, W, N; 
  cin >> H >> W >> N; 
  vector<pair<int, int>>coord(N); 
  for(int i = 0; i < N; i++) { 
    cin >> coord[i].first >> coord[i].second; 
  }
  vector<int64_t>dyn(N); 
  sort(coord.begin(), coord.end()); 
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) { 
    dyn[i] = Comb(coord[i].first + coord[i].second - 2, coord[i].first - 1); 
    for(int j = 0; j < i; j++) { 
      if(coord[j].second <= coord[i].second) {
        int distx = coord[i].first  - coord[j].first; 
        int disty = coord[i].second - coord[j].second; 
        dyn[i] = (dyn[i] - dyn[j] % mod * Comb(distx + disty, distx) % mod + mod) % mod; 
      }
    }
    ret += dyn[i] % mod * Comb(H - coord[i].first + W - coord[i].second, H - coord[i].first) % mod; 
    ret %= mod; 
  }
  ret = (Comb(H + W - 2, W - 1) - ret + mod) % mod; 
  cout << ret << '\n'; 
  return 0;
}
/*
  dyn[i] = {number of ways to reach (H, W) with the ith obstacles being the first obstacles in the path}
  dyn[i] = dyn[j]
*/