#include "bits/stdc++.h"

using namespace std;

struct fenwick {
  int N;
  vector<int64_t> bit;
  void init(int _N) {
    N = _N;
    bit.resize(N + 2);
    return;
  }
  int64_t sum(int i) {
    int64_t c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = max(c, bit[i]);
    }
    return c;
  }
  void upd(int i, int64_t dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = max(dif, bit[i]);
    }
    return; 
  }
};

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<int>a(N), h(N); 
  for(int i = 0; i < N; i++) { 
    cin >> h[i]; 
  }
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  fenwick fenw; 
  fenw.init(N + 2); 
  vector<int64_t>dyn(N); 
  for(int i = 0; i < N; i++) { 
    dyn[i] = a[i] + fenw.sum(h[i] - 1); 
    fenw.upd(h[i], dyn[i]); 
  }
  int64_t ret = *max_element(dyn.begin(), dyn.end()); 
  cout << ret << '\n'; 
  return 0; 
}