#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int MOD = 998244353; 

class FarmerJohn { 
  public:   
   void solve() { 
    int N, M; 
    cin >> N >> M; 
    vector<vector<int>>hands(N, vector<int>(M)); 
    for(int i = 0; i < N; i++) { 
     for(int j = 0; j < M; j++) { 
      cin >> hands[i][j]; 
     }
     sort(hands[i].rbegin(), hands[i].rend()); 
    } 
    vector<int>ord(N); 
    iota(ord.begin(), ord.end(), 0); 
    sort(ord.begin(), ord.end(), [&](int u, int v) { 
     return hands[u].back() < hands[v].back(); 
    });  
    // sanity
    int last_card = -1; 
    for(; last_card < N * M - 1; ) { 
     for(auto &x : ord) { 
      if(hands[x].back() > last_card) { 
        last_card = hands[x].back(); 
        hands[x].pop_back(); 
      } else { 
        cout << -1 << '\n'; 
        return; 
      }
     }
    } 
    for(auto &x : ord) cout << x + 1 << " "; 
    cout << '\n'; 
    return; 
   }
};


int main(void) {  
 int T; 
 FarmerJohn problem; 
 for(cin >> T; T--; ) { problem.solve(); }
 return 0; 
}