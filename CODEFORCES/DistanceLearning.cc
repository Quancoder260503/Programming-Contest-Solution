#include "bits/stdc++.h"

using namespace std; 

struct Tree {
  typedef int T;
  static constexpr T unit = 0;
  T f(T a, T b) { return a | b; }  // (any associative fn)
  vector<T> s;
  int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    pos += n; 
    s[pos] = f(val, s[pos]);
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

const int LOG = 31; 

void solve() {
  int N, Q; 
  cin >> N; 
  vector<int>l(N), r(N), w(N); 
  // w[i] is the longest common prefix of l[i] and r[i] in binary. 
  for(int i = 0; i < N; i++) { 
    cin >> l[i] >> r[i];
    if(l[i] == r[i]) {
      w[i] = l[i]; 
      r[i] = l[i] = 0; 
    }
    else {
      int prefix = (1 << (__lg(r[i] ^ l[i]) + 1)) - 1; 
      w[i] = r[i] - (r[i] & prefix);
      r[i] &= prefix; // set of different bits of r[i]
      l[i] &= prefix; // set of different bits of l[i] 
    } 
  //  cout << l[i] << " " << r[i] << " " << '\n'; 
  }
  Tree tree(N); 
  vector<vector<int>>cnt(LOG, vector<int>(N + 1)); 
  for(int i = 0; i < N; i++) {
    tree.update(i, w[i]);
    for(int j = LOG - 1; j >= 0; j--) { 
      cnt[j][i + 1] = cnt[j][i]; 
      if(r[i] >> j & 1) { 
        cnt[j][i + 1]++; 
      } 
    } 
  } 
  cin >> Q; 
  for(int i = 0, x, y; i < Q; i++) { 
    cin >> x >> y;
    --x, --y; 
    int ret = tree.query(x, y + 1); 
    for(int j = LOG - 1; j >= 0; j--) {
      int ctr = cnt[j][y + 1] - cnt[j][x] + (ret >> j & 1);
      if(ctr > 1) {
        ret |= (2 << j) - 1; 
        break; 
      } 
      else if(ctr == 1) { 
        ret |= (1 << j);
      } 
    }
    cout << ret << " "; 
  } 
  cout << '\n'; 
  return;   
}


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Tc;
  for(cin >> Tc; Tc--; ) { 
    solve(); 
  } 
  return 0; 
}