#include <bits/stdc++.h>
 
using namespace std;
 
const int BASE = 20;
const int MOD = 1e9 + 7;
 
struct linear_basis {
 int64_t A[BASE + 1];
 int64_t count;
 bool flag;
 linear_basis() {
  memset(A, 0, sizeof(A));
  count = 0;
  flag = false;
 }
 void add(int64_t val) {
  for (int mask = BASE; mask >= 0; mask--) {
   if (val & (1LL << mask)) {
    if (A[mask]) {
     val = val ^ A[mask];
    } else {
     A[mask] = val;
     return;
    }
   }
  }
 }
};
 
int main() {
 int N;
 cin >> N;
 vector<int64_t> a(N); 
 linear_basis basis; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  basis.add(a[i]); 
 } 
 int64_t dim = 0, ans = 1;
 for(int j = 0; j < BASE + 1; j++) { 
   dim += (basis.A[j] > 0); 
 } 
 for(int j = 0; j < N - dim; j++) {
  ans = ans * 2 % MOD; 
 } 
 cout << ans << '\n'; 
 return 0;
}