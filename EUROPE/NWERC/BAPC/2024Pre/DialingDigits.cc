#include "bits/stdc++.h"
using namespace std; 

#define sz(x) int(x.size())

class Dialing { 
public: 
  void solve() { 
   int N, Q; 
   cin >> N >> Q; 
   vector<int>pos = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9}; 
   unordered_map<int64_t, vector<string>>mp; 
   for(int i = 0; i < N; i++) { 
    string cc; 
    cin >> cc; 
    int64_t ans = 0; 
    for(int j = 0; j < sz(cc); j++) { 
     ans = 10LL * ans + pos[cc[j] - 'a']; 
    } 
    mp[ans].push_back(cc); 
   }
   for(int i = 0; i < Q; i++) { 
    int64_t x; 
    cin >> x;
    vector<string>&cc = mp[x]; 
    cout << sz(cc) << " "; 
    for(auto &y : cc) cout << y << " "; 
    cout << '\n'; 
   }
   return;  
  }
}; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 Dialing diag; 
 diag.solve(); 
 return 0; 
}