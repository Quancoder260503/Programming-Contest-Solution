#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
class Pepper { 
 public :
   void solve() { 
    int N; 
    cin >> N; 
    vector<int>deg(N); 
    for(int i = 0, u, v; i < N - 1; i++) { 
     cin >> u >> v;
     --u, --v; 
     deg[u]++; 
     deg[v]++; 
    }
    int cnt = 0; 
    for(int i = 0; i < N; i++) { 
     cnt += (deg[i] >= 3); 
    }
    cout << (cnt <= 1 ? "Codeforces and Boba" : "SPAR 27th April") << '\n'; 
    return; 
   }
}; 
 
int main(void) { 
  Pepper problem; 
  problem.solve(); 
  return 0; 
}