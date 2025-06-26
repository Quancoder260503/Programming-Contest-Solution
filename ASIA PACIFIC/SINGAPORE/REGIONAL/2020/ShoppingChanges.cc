#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int oo = 1e9; 

struct Fenwick { 
 vector<int64_t>bit; 
 int N; 
 Fenwick(int _N) { 
   N = _N; 
   bit.resize(N); 
 }
 int64_t sum(int pos) {
  int64_t ret = 0;  
  for(++pos; pos > 0; pos -= (pos & -pos)) { 
   ret += bit[pos]; 
  }
  return ret; 
 }
 int64_t query(int L, int R) { 
  return sum(R) - sum(L - 1);  
 }
 void update(int pos, int v) { 
  for(++pos; pos < N; pos += (pos & -pos)) { 
   bit[pos] += v; 
  }
  return; 
 }
}; 
 
class Shopping { 
 public :
  void solve() { 
  int N, Q; 
  cin >> N >> Q; 
  vector<int>a(N);
  vector<vector<int>>c(Q); 
  vector<int>coord; 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
   coord.push_back(a[i]); 
  }
  for(int i = 0, M; i < Q; i++) { 
    cin >> M; 
    c[i].resize(M); 
    for(int j = 0; j < M; j++) { 
     cin >> c[i][j]; 
     coord.push_back(c[i][j]); 
    }
  }
  sort(coord.begin(), coord.end()); 
  coord.erase(unique(coord.begin(), coord.end()), coord.end()); 

  for(int i = 0; i < N; i++) { 
    a[i] = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin() + 1; 
  }
  for(int i = 0; i < Q; i++) { 
   for(int j = 0; j < sz(c[i]); j++) { 
    c[i][j] = lower_bound(coord.begin(), coord.end(), c[i][j]) - coord.begin() + 1; 
   }
  }
  Fenwick fw(400200);  
  int64_t inversion = 0; 
  for(int i = 0; i < N; i++) { 
   fw.update(a[i], 1); 
   inversion += fw.query(a[i] + 1, 400000); 
  }
  vector<int>invL(400002), invR(400002); 
  for(int i = 0; i < sz(invL); i++) { 
   invL[i] = fw.query(0, i - 1); 
   invR[i] = fw.query(i + 1, 400000);  
  }
  for(int i = 0; i < N; i++) { 
    fw.update(a[i], -1); 
  } 
  for(int i = 0, M; i < Q; i++) { 
   int64_t ans = 0, curr = 0, curr_inv = 0; 
   for(int j = 0; j < sz(c[i]); j++) { 
    curr += invR[c[i][j]]; 
    curr_inv += fw.query(c[i][j] + 1, 400000); 
    fw.update(c[i][j], 1); 
   }
   ans = curr; 
   for(int j = 0; j < sz(c[i]); j++) { 
    fw.update(c[i][j], -1); 
    curr = curr - invR[c[i][j]] + invL[c[i][j]]; 
    ans = min(ans, curr); 
   }
   ans += inversion + curr_inv; 
   cout << ans << '\n'; 
  }
  return;  
 } 
}; 
 
int main(void) { 
  Shopping task; 
  task.solve(); 
  return 0; 
}