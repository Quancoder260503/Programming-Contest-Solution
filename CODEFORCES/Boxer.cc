#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

class Boxer { 
  public:   
   void solve() { 
    int N; 
    cin >> N; 
    vector<int>a(N); 
    for(int i = 0; i < N; i++) { 
     cin >> a[i]; 
    }
    sort(a.rbegin(), a.rend()); 
    int last = a[0] + 2, ans = 0; 
    for(int i = 0; i < N; i++) {
     int c = -1;  
     for(int curr = 1; curr >= -1; curr--) { 
      if(curr + a[i] > 0 && curr + a[i] < last) { 
        c = curr + a[i]; 
        break; 
      }
     }
     if(c == -1) continue; 
     last = c; 
     ans++; 
    }
    cout << ans << '\n'; 
    return; 
   }
};


int main(void) {  
 Boxer boxer; 
 boxer.solve(); 
 return 0; 
}