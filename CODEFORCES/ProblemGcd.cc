#include "bits/stdc++.h"
 
using namespace std;
 
#define int64_t long long 
 
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { 
   int64_t L, R, G; 
   cin >> L >> R >> G;
   L = L / G + (L % G > 0); 
   R = R / G; 
   array<int64_t, 3>ans = {-1, -1, -1}; 
   for(int64_t j = L; j <= L + 100; j++) {
    for(int64_t i = R; i >= j; i--) { 
     if(gcd(i, j) == 1) { 
      ans = max(ans, {i - j, -j, i});
      break;  
     }
    }
   } 
   if(ans[0] == -1) cout << -1 << " " << -1 << '\n'; 
   else {
    cout << -ans[1] * G << " " << ans[2] * G << '\n'; 
   } 
  }
  return 0;
}