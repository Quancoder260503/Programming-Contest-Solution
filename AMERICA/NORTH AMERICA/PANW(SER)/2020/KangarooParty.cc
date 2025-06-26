#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  int N; 
  cin >> N; 
  vector<int>rx(N); 
  for(int i = 0; i < N; i++) { 
   cin >> rx[i]; 
  }
  int64_t ans = LLONG_MAX; 
  for(int i = 0; i < N; i++) { 
   for(int j = 0; j < N; j++) { 
    int64_t tot = 0; 
    for(int k = 0; k < N; k++) { 
     tot += min(1LL * (rx[k] - rx[i]) * (rx[k] - rx[i]), 1LL * (rx[k] - rx[j]) * (rx[k] - rx[j]));
    }
    ans = min(ans, tot); 
   }
  }
  cout << ans << '\n'; 
  return 0; 
}
