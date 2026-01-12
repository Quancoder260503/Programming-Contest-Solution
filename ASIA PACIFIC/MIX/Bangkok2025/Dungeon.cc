#include <vector> 
#include <iostream> 
#include <assert.h>
#include <functional>
#include <set> 
 
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std; 
 
const int maxn = 5e5 + 10; 
const int MOD = 998244353; 
const int oo = 1e8; 
 
using ll = long long; 
 
#define sz(x) int(x.size())
 
struct segtree { 
 vector<pair<int, int>> tree; 
 int n; 
 segtree(int _n) : n(_n), tree(4 * _n, {oo, -1}) {}; 
 void update(int v, int pos, int vl, int vr, int p) {  
  if(vl == vr) { 
   tree[p] = (v == -oo ? make_pair(v, -1) : make_pair(v, vl));  
   return;  
  } 
  int mid = (vl + vr) / 2; 
  if(pos <= mid) update(v, pos, vl, mid, p << 1); 
  else           update(v, pos, mid + 1, vr, p << 1 | 1); 
  tree[p] = min(tree[p << 1], tree[p << 1 | 1]); 
  return;  
 }
 pair<int, int> query(int L, int R, int vl, int vr, int p) { 
  if(R < vl | vr < L) return {oo, -1}; 
  if(L <= vl && vr <= R) return tree[p]; 
  int mid = (vl + vr) / 2; 
  return min(query(L, R, vl, mid, p << 1), query(L, R, mid + 1, vr, p << 1 | 1)); 
 } 
};
 
ll mod_pow(ll a, ll p, int MOD) { 
 ll ret = 1; 
 while(p) { 
  if(p & 1) ret = ret * a % MOD; 
  a = a * a % MOD; 
  p = p / 2; 
 }
 return ret; 
}
 
ll mod_inv(ll a, int MOD) { return mod_pow(a, MOD - 2, MOD); }
 
// check modulo
void FST(vector<ll>& a, bool inv) {
 for(int n = sz(a), step = 1; step < n; step *= 2) {
  for(int i = 0; i < n; i += 2 * step) { 
   for(int j = i; j < i + step; j++) {
    ll &u = a[j], &v = a[j + step]; 
    tie(u, v) = make_pair((u + v) % MOD, (u - v + MOD) % MOD); 
   }
  }
 }
 if (inv) { 
  ll den = mod_inv(sz(a), MOD); 
  for (ll &x : a) x = x * den % MOD;
 } 
 return; 
}
 
vector<ll> poly_pow(vector<ll> a, int R) {
 FST(a, 0); 
 for(int i = 0; i < sz(a); i++) { 
  a[i] = mod_pow(a[i], R, MOD); 
 }
 FST(a, 1); 
 return a;
}
 
 
int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 int n, K, r; 
 cin >> n >> K >> r; 
 vector<int>a(n + 1), grundy(n + 1), dp(n + 1, -1), last(n + 1, -1); 
 for(int i = 1; i <= n; i++) cin >> a[i];
 segtree tree(n + 2); 

 tree.update(grundy[0], 0, 0, n, 1); 
 last[grundy[0]] = 0; 
/*
 function<int(int)>Grundy = [&](int x) { 
  if(x == 0) return 0; 
  int &ret = dp[x]; 
  if(ret != -1) return ret; 
  ret = 0; 
  set<int>ms; 
  for(int d = 1; d <= a[x]; d++) { 
   ms.insert(Grundy(x - d)); 
  }
  while(ms.count(ret)) ret++; 
  return ret; 
 }; 
*/

 // Sweepline 
 set<int>ms{0}; 
 for(int i = 1; i <= n; i++) { 
  grundy[i] = tree.query(0, i - a[i] - 1, 0, n, 1).first;
  if(grundy[i] == oo) grundy[i] = *prev(ms.end()) + 1; 
  if(last[grundy[i]] != -1) { 
   tree.update(oo, last[grundy[i]], 0, n, 1); 
  }  
  last[grundy[i]] = i; 
  tree.update(grundy[i], i, 0, n, 1);
  ms.insert(grundy[i]); 
 // cerr << grundy[i] << '\n'; 
 } 
 vector<ll>poly(1 << 19), poly_b(1 << 19); 
 for(int i = 0; i <= n; i++) { 
  poly[grundy[i]]++;  
 }
 poly = poly_pow(poly, r); 
 for(int i = 0; i <= n; i++) if(i + K > n || grundy[i] == grundy[i + K]) { 
  poly_b[grundy[i]]++;   
 } 
 poly_b = poly_pow(poly_b, r);
 //cerr << poly[0] << " " << poly_b[0] % MOD << '\n'; 
 ll ans = (poly[0] - poly_b[0] + MOD) % MOD;  
 cout << ans << '\n'; 
 return 0; 
}