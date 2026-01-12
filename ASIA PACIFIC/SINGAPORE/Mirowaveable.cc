#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxn = 3e5 + 2; 

int n, m, a[maxn]; 
vector<int>g[maxn]; 

 
struct FT {
  int N;
  vector<int> bit;
  FT(int _N) {
    N = _N;
    bit.resize(N);
  }
  int query(int i) {
    int c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c + bit[i];
    }
    return c;
  }
  int query(int l, int r) { 
    if(l > r) return 0; 
    return query(r) - query(l - 1); 
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
 cin >> n >> m; 
 unordered_map<int, int>cnt; 
 vector<int>lst(m, -1); 
 for(int i = 1, x; i <= n; i++) { 
  cin >> a[i]; 
  --a[i]; 
  cnt[a[i]]++; 
 }
 FT fenw(n + 2); 
 int64_t ret = 0; 
 for(int pivot = n; pivot > 0; pivot--) {
  if(lst[a[pivot]] == -1) { 
   fenw.update(pivot, 1); 
   lst[a[pivot]] = pivot;  
   ret += m - 1; 
  } else { 
   int last = lst[a[pivot]]; 
   ret += fenw.query(pivot + 1, last - 1); 
   //cout << pivot + 1 << " " << last - 1 << '\n'; 
   fenw.update(last, -1); 
   fenw.update(pivot, 1); 
   lst[a[pivot]] = pivot; 
  }
 }
 cout << ret << '\n'; 
 return 0; 
}