#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 1e6 + 3; 

class Chloe {
public:
 void solve() {
  int N; 
  cin >> N;
  int64_t ans = 0;   
  for(int i = 0, x; i < N; i++) { 
   cin >> x; 
   if(x <= N - i) { 
    ans += (ans + x) / (N - i); 
    ans %= MOD; 
   }
  } 
  cout << ans << '\n'; 
  return;
 }
};

int main(void) {
 Chloe problem;
 problem.solve();
 return 0;
}