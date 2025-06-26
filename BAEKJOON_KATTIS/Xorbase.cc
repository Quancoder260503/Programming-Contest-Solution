#include "bits/stdc++.h"
 
using namespace std;
 
const int BASE = 31;
 
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
 
void solve() {
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
 if(N == dim) { 
  cout << "YES\n"; 
 } else { 
  cout << "NO " << N - dim << '\n'; 
 } 
}

int main(void) { 
 int T;
 for(cin >> T; T--; ) solve(); 
 return 0; 
}