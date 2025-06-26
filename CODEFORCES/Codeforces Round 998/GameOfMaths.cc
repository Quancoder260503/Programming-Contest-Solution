#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int MOD = 998244353; 

class GameOfMaths { 
  public:   
   void solve() { 
    int N, K; 
    cin >> N >> K;
    map<int, int>mp; 
    int ans = 0; 
    for(int i = 0, x; i < N; i++) { 
     cin >> x; 
     if(mp.count(K - x)) { 
      ans++; 
      mp[K - x]--; 
      if(mp[K - x] == 0) mp.erase(K - x); 
     } else { 
      mp[x]++; 
     }
    }
    cout << ans << '\n'; 
    return; 
   }
};


int main(void) {  
 int T; 
 GameOfMaths problem; 
 for(cin >> T; T--; ) { problem.solve(); }
 return 0; 
}