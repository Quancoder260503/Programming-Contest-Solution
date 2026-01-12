#include "bits/stdc++.h"

using namespace std;  

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n, m; 
  cin >> n >> m; 
  vector<int>dp(m); 
  for(int i = 0, x; i < n; i++) { 
   cin >> x;  
   vector<int>ndp(dp.begin(), dp.end()); 
   ndp[x % m] = 1; 
   for(int j = 0; j < m; j++) { 
    ndp[(x + j) % m] |= dp[j]; 
   }
   dp.swap(ndp); 
   if(dp[0]) { 
    cout << "YES\n"; 
    exit(0); 
   }
  }
  cout << "NO\n";  
  return 0; 
}
