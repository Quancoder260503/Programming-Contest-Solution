#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

class Lobotomy { 
  public:   
   void solve() { 
    int N; 
    cin >> N; 
    vector<int>a(1001); 
    for(int i = 0, x; i < N; i++) { 
     cin >> x; 
     a[x]++; 
    } 
    int ans = 0; 
    for(;;) { 
     int opt = 1000000; 
     for(int i = 0; i < sz(a); i++) { 
      if(a[i] == 0) continue; 
      opt = min(opt, a[i]);   
     }
     if(opt == 1000000) break;
     for(int i = 0; i < sz(a); i++) { 
      if(a[i] == 0) continue; 
      a[i] -= opt; 
     }
     ans += opt; 
    }
    cout << ans << '\n'; 
    return; 
   }
};


int main(void) {  
 Lobotomy problem;
 problem.solve(); 
 return 0; 
}