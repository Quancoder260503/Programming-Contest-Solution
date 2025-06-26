#include "bits/stdc++.h"

using namespace std;

struct fenwick {
  int N;
  vector<int> bit;
  void init(int _N) {
    N = _N;
    bit.resize(N + 10);
    return;
  }
  int sum(int i) {
    int c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c ^ bit[i];
    }
    return c;
  }
  void upd(int i, int diff) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = diff ^ bit[i];
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
  vector<int>aux; 
  vector<tuple<int, int, int, int>>events; 
  for(int i = 0, x, y; i < N; i++) { 
    cin >> x >> y; 
    aux.push_back(y); 
    events.push_back({x, true, y, i + 1}); 
  }
  int last_x = -1, last_y = -1, first_x = -1, first_y = -1; 
  for(int i = 0, x, y; i < M; i++) { 
    cin >> x >> y; 
    aux.push_back(y); 
    if(!i) { first_x = x, first_y = y; }
    if(i > 0 && last_x == x) events.push_back({x, false, y, last_y}); 
    last_x = x, last_y = y; 
  }
  if(last_x == first_x) { events.push_back({last_x, false, first_y, last_y}); }
  sort(aux.begin(), aux.end()); 
  sort(events.begin(), events.end()); 
  int64_t ret = 0; 
  fenwick fenw;
  fenw.init(aux.size() + 1); 
  for(auto [x, type, ya, yb] : events) { 
    ya = lower_bound(aux.begin(), aux.end(), ya) - aux.begin(); 
    if(type) { 
      if(!fenw.sum(ya)) ret += yb; 
    }
    else { 
      yb = lower_bound(aux.begin(), aux.end(), yb) - aux.begin(); 
      fenw.upd(ya, 1); 
      fenw.upd(yb, 1); 
    }
  }
  cout << ret << '\n'; 
  return 0;
}