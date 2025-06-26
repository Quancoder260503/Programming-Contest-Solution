#include "bits/stdc++.h"

using namespace std;

struct FT {
  int N;
  vector<int64_t> bit;
  FT(int _N) {
    N = _N;
    bit.resize(N);
  }
  int64_t sum(int i) {
    int64_t c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c + bit[i];
    }
    return c;
  }
  int64_t query(int L, int R) { 
   return sum(R) - sum(L - 1); 
  }
  void update(int i, int dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = dif + bit[i];
    }
  }
};
 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, D; 
  cin >> N; 
  vector<int>a(N);   
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  vector<int>ord(N); 
  iota(ord.begin(), ord.end(), 0); 
  sort(ord.begin(), ord.end(), [&](int u, int v) { 
   return a[u] > a[v]; 
  }); 
  FT fenw_coord(N + 2); 
  FT fenw(N + 2);
  int64_t ret = 0;  
  for(int i = 0; i < ord.size(); i++) { 
   int x = ord[i] + 1;
   int64_t cnt = fenw_coord.query(x + 1, N), cnt_sum = fenw.query(x + 1, N); 
   ret += 1LL * cnt_sum - 1LL * cnt * a[x - 1]; 
   fenw.update(x, a[x - 1]);
   fenw_coord.update(x, 1); 
  }
  cout << ret << '\n'; 
  return 0; 
}
