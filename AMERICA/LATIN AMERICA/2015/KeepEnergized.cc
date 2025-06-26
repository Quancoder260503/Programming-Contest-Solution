#include "bits/stdc++.h"

using namespace std;

const int oo = 1e9 + 10; 

struct fenwick {
  int N;
  vector<int> bit;
  void init(int _N) {
    N = _N;
    bit.resize(N + 10, oo);
    return;
  }
  int sum(int i) {
    int c = oo;
    for (++i; i > 0; i -= (i & -i)) {
      c = min(c, bit[i]);
    }
    return c;
  }
  void upd(int i, int dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = min(dif, bit[i]);
    }
    return; 
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, M;
  cin >> N >> M;
  vector<int> E(N), suffix(N + 1), dyn(N + 2, oo);
  for (int i = 0; i < N; i++) {
    cin >> E[i];
  }
  for (int i = N - 1; i >= 0; i--) {
    suffix[i] = suffix[i + 1] + E[i];
  }
  vector<vector<pair<int, int>>> offer(N);
  for (int i = 0, l, c, s; i < M; i++) {
    cin >> l >> s >> c;
    offer[--l].push_back({c, s});
  }
  dyn[N + 1] = 0;
  fenwick fenw;
  fenw.init(N + 1); 
  for (int i = N - 1; i >= 0; i--) {
    for (auto [c, s] : offer[i]) {
      if(E[i] > s) continue; 
      if(s >= suffix[i]) { 
        dyn[i] = min(dyn[i], c); 
        continue; 
      }
      int lo = i + 1, hi = N - 2;
      while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (suffix[i] - suffix[mid + 1] <= s) {
          lo = mid + 1;
        } else {
          hi = mid - 1;
        }
      }
      dyn[i] = min(dyn[i], c + fenw.sum(lo));
    }
    fenw.upd(i, dyn[i]); 
  }
  cout << (dyn[0] == oo ? -1 : dyn[0]) << '\n'; 
  return 0;
}