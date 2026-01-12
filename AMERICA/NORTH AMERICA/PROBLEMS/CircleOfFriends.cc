#include "bits/stdc++.h"

using namespace std;

const int MOD = 998244353; 

#define sz(x) int(x.size())
#define rep(i, j, k) for(int i = j; i < k; i++)

template<class T>
struct RMQ {
 vector<vector<T>> jmp;
 RMQ(const vector<T>& V) : jmp(1, V) { 
  for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
   jmp.emplace_back(sz(V) - pw * 2 + 1);
   rep(j,0,sz(jmp[k]))
	jmp[k][j] = jmp[k - 1][j] & jmp[k - 1][j + pw];
   }
 }
 T query(int a, int b) {
  //assert(a < b); // or return inf if a == b
  if(a == b) return 0; 
  int dep = 31 - __builtin_clz(b - a);
  return jmp[dep][a] & jmp[dep][b - (1 << dep)];
 }
};

struct Fenwick { 
 int n; 
 vector<int64_t>bit; 
 Fenwick(int _n) : n(_n) { 
  bit.resize(n); 
 }
 void upd(int p, int64_t v) { 
  for(p++; p < n; p += p & (-p)) { 
   bit[p] += v;  
  }
 }
 int64_t query(int p) {
  int64_t ret = 0;  
  for(p++; p > 0; p -= p & (-p)) { 
   ret += bit[p]; 
  }
  return ret; 
 }
 int64_t query(int L, int R) { 
  return L > R ? 0 : query(R) - query(L - 1); 
 }
 void reset() { 
  fill(bit.begin(), bit.end(), 0); 
 }
}; 

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
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n; 
 cin >> n; 
 vector<int64_t>a(n); 
 for(auto &x : a) cin >> x; 
 int64_t g = a[0]; 
 for(int i = 0; i < n; i++) { 
  g = g & a[i]; 
 }
 if(g > 0) { 
  cout << (mod_pow(2, n, MOD) - n + MOD) % MOD << '\n' << '\n';  
  return 0; 
 }
 vector<int64_t>dp(n); 
 RMQ rmq(a);  
 Fenwick fenw(n + 2); 
 for(int i = 0; i < n; i++) { 
  int lo = -1, hi = i; 
  dp[i] = 0; 
  while(lo < hi) {
   int mid = (lo + hi + 1) / 2; 
   if(rmq.query(mid, i + 1) > 0) hi = mid - 1; 
   else lo = mid; 
  }
  // [lo + 1, i] with g > 1
  dp[i] = (i ? dp[i - 1] : 1) * (a[i] > 0); 
  dp[i] += fenw.query(lo + 1, i - 1); 
  dp[i] %= MOD; 
  fenw.upd(i, i ? dp[i - 1] : 1); 
 }
 int ptr = n - 1;  
 g = dp[ptr]; 
 int64_t ret = dp[ptr];
 while(1) { 
  a[0] = a[0] & a[ptr]; 
  if(a[0] == 0) break; 
  if(g != a[0]) { 
   fenw.reset(); 
   RMQ rmq_cc(a);  
   for(int i = 0; i < n; i++) { 
    int lo = -1, hi = i; 
    dp[i] = 0; 
    while(lo < hi) {
     int mid = (lo + hi + 1) / 2; 
     if(rmq_cc.query(mid, i + 1) > 0) hi = mid - 1; 
     else lo = mid; 
    }
  // [lo + 1, i] with g > 1
    dp[i] = (i ? dp[i - 1] : 1) * (a[i] > 0); 
    dp[i] += fenw.query(lo + 1, i - 1); 
    dp[i] %= MOD; 
    fenw.upd(i, i ? dp[i - 1] : 1); 
   }
  } 
  //cout << dp[ptr - 1] << '\n'; 
  ret += dp[ptr - 1]; 
  ret %= MOD; 
  ptr--; 
  g = a[0];   
 } 
 cout << ret << '\n'; 
 return 0; 
}

/// 2 ^ (N - 1) - 1 
/// 2 ^ (N - 2) - 1
/// 2 ^ (N - 3) - 1 
/// 2 ^ N - N