#include "bits/stdc++.h"

using namespace std; 

void solve() {  
 int N, C; 
 cin >> N >> C; 
 vector<int>a(N); 
 int even = 0, odd = 0; 
 int64_t ret = 0; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  ret = ret - a[i] / 2 - 1; 
  ret = ret - (C - a[i] + 1); 
  (a[i] % 2 == 0 ? even : odd)++; 
 }
 ret += 1LL * (C + 1) * (C + 2) / 2; 
 ret = ret + 1LL * even * (even + 1) / 2; 
 ret = ret + 1LL * odd  * (odd  + 1) / 2; 
 cout << ret << '\n'; 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { solve(); }
  return 0; 
}
