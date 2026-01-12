#include "bits/stdc++.h"

#define sz(x) int(x.size())

using namespace std; 

const int oo = 1e9 + 10; 

struct Tree {
 typedef int T;
 static constexpr T unit = oo; 
 T f(T a, T b) { return min(a, b); }  // (any associative fn)
 vector<T> s;
 int n;
 Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
 void update(int pos, T val) {
  s[pos += n] = val; 
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

template<class T>
ostream &operator  << (ostream &out, pair<T, T>&c) {
 out << c.first << " " << c.second;
 return out; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int n, m; 
 cin >> n;
 vector<int>a(n); 
 for(auto &x : a) { 
  cin >> x; 
 }
 cin >> m; 
 vector<int>b(m);
 for(auto  &x : b) { 
  cin >> x; 
 }
 Tree segtree(n + 2); 
 for(int i = 0; i < n; i++) { 
  segtree.update(i + 1, a[i]); 
 }  
 set<int>ms; 
 for(int i = 0; i < m; i++) { 
  // find the first position
  int lo = 1, hi = n, pos = -1; 
  b[i]++; 
  while(lo <= hi) { 
   int mid = (lo + hi) / 2; 
   if(segtree.query(1, mid + 1) < b[i]) { 
    hi = mid - 1; 
    pos = mid; 
   } else lo = mid + 1; 
  }
  if(pos != -1) { 
   segtree.update(pos, b[i]); 
   ms.insert(pos);
  }
 }
 cout << sz(ms) << '\n'; 
 return 0; 
}