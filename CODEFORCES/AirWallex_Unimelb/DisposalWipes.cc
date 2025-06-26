#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
class Disposal { 
 public :
   void solve() { 
    int64_t X, Y; 
    cin >> X >> Y; 
    int cnt = 0; 
    while(X >= Y) { 
     cnt++; 
     X = X / 2; 
    }
    cout << cnt << '\n'; 
    return; 
   }
}; 
 
int main(void) { 
  Disposal problem; 
  problem.solve(); 
  return 0; 
}