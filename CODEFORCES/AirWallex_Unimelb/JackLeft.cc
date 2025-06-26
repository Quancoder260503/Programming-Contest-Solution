#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
class JackLeft { 
 public :
   void solve() { 
    int N; 
    cin >> N; 
    int ans = 0; 
    map<int, int>mp; 
    for(int i = 0, y, x; i < N; i++) { 
     cin >> y >> x; 
     mp[y] += x; 
    }
    for(auto [_, x] : mp) { 
     ans += x / N + x % N; 
    }
    cout << ans << '\n'; 
    return; 
   }
}; 
 
int main(void) { 
  JackLeft problem; 
  problem.solve(); 
  return 0; 
}