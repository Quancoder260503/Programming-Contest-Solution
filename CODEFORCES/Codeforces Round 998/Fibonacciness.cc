#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

class Fibonaccines { 
  public:   
   void solve() { 
    vector<int>a(5);  
    cin >> a[0] >> a[1] >> a[3] >> a[4]; 
    int ret = 0; 
    for(int i = -100; i <= 100; i++) { 
     int c = 0;
     a[2] = i;  
     for(int j = 2; j < 5; j++) { 
      c += (a[j] == a[j - 1] + a[j - 2]); 
     }
     ret = max(ret, c); 
    }
    cout << ret << '\n'; 
    return; 
   }
};


int main(void) {  
 int T; 
 Fibonaccines problem; 
 for(cin >> T; T--; ) { problem.solve(); }
 return 0; 
}