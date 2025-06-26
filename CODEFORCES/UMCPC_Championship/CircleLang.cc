#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

class CircleLang { 
  public:   
   void solve() { 
    int N;
    string a, b;
    cin >> N >> a >> b; 
    sort(a.begin(), a.end()); 
    sort(b.begin(), b.end()); 
    cout << (a == b ? "Yes" : "No") << '\n'; 
   }
};


int main(void) {  
 CircleLang problem; 
 problem.solve();
 return 0; 
}