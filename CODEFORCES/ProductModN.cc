#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

class ProductMod { 
  public:   
   void solve() { 
    int N; 
    cin >> N; 
    vector<int>ans; 
    int64_t prod = 1; 
    for(int i = 1; i <= N; i++) { 
      if(gcd(i, N) == 1) { 
       ans.push_back(i); 
       prod = (prod * i) % N; 
      }  
    }
    if(prod > 1) { 
     ans.pop_back(); 
    }
    cout << sz(ans) << '\n'; 
    for(auto &x : ans) cout << x << " "; 
    cout << '\n'; 
   }
};


int main(void) {  
 ProductMod problem; 
 problem.solve(); 
 return 0; 
}