#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MAX_BOUND = 300000;

struct Tree {
 typedef int T;
 static constexpr T unit = 0;
 T f(T a, T b) { return max(a, b); }  // (any associative fn)
 vector<T> s;
 int n;
 Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
 void update(int pos, T val) {
  pos += n;
  s[pos] = max(s[pos], val); 
  for (; pos /= 2;) s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
 }
 T query(int b, int e) {  // query [b, e)
  T ra = unit, rb = unit;
  for (b += n, e += n; b < e; b /= 2, e /= 2) {
   if (b % 2) ra = f(ra, s[b++]);
   if (e % 2) rb = f(s[--e], rb);
  }
  return f(ra, rb);
 }
};

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K;
 cin >> N >> K;
 Tree tree_opt(MAX_BOUND + 10); 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  int opt = 1 + tree_opt.query(max(0, x - K), min(x + K, MAX_BOUND) + 1);
  tree_opt.update(x, opt);  
 }
 cout << tree_opt.query(0, MAX_BOUND + 2) << '\n'; 
 return 0; 
}