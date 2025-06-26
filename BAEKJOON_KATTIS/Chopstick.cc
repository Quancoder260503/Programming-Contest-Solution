#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int oo = 1e9; 
 
class Chopstick { 
 public :
  void solve() { 
  int N; 
  cin >> N; 
  int64_t num_ones = 0, num_twos = 0;  
  for(int i = 0, x; i < N; i++) { 
   cin >> x; 
   num_ones += max(x - 2, 0);
   num_ones += (x == 1);  
   num_twos += (x >= 2); 
  }
  int64_t ans = num_ones / 2 + num_twos / 2; 
  cout << ans << '\n'; 
  return;  
 } 
}; 
 
int main(void) { 
  Chopstick task; 
  int T; 
  cin >> T; 
  while(T--) { 
   task.solve(); 
  } 
  return 0; 
}