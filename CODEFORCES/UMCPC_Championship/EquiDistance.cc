#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

class EqualDistance { 
  public:   
   void solve() { 
     int N; 
     cin >> N; 
     int max_dist = 0; 
     vector<vector<int>>g(N, vector<int>(N)); 
     for(int i = 0; i < N; i++) { 
      for(int j = 0; j < N; j++) { 
       cin >> g[i][j]; 
       max_dist = max(max_dist, g[i][j]); 
      }
     }
     int start = -1, end = -1; 
     for(int i = 0; i < N; i++) { 
      for(int j = 0; j < N; j++) { 
       if(max_dist == g[i][j]) { 
        start = i, end = j; 
        goto done; 
       }
      }
     }
done:;
     int check = true;  
     for(int i = 0; i < N; i++) { 
      if(i == end || i == start) continue; 
      check = check & (g[start][i] == max_dist || g[end][i] == max_dist); 
     }
     if(!check || (max_dist & 1)) { 
      cout << -1 << '\n'; 
      return; 
     }
     cout << (max_dist / 2) << '\n';
   }
};


int main(void) {  
 EqualDistance Problem; 
 Problem.solve(); 
 return 0; 
}