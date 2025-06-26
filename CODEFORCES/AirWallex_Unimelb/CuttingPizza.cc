#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
class Pizza { 
 public :
   void solve() { 
    int d1; 
    cin >> d1; 
    for(int d2 = d1 + 1; d2 <= 179; d2++) { 
      vector<int>perm = {0, 1, 2}; 
      vector<int>arr = {d1, d2 - d1, 180 - d2}; 
      do { 
        int x_a = d1       + arr[perm[0]]; 
        int x_b = d2 - d1  + arr[perm[1]];
        int x_c = 180 - d2 + arr[perm[2]];  
        if(x_a == x_b && x_b == x_c) { 
         cout << d2 << '\n'; 
         return; 
        }
      }
      while(next_permutation(perm.begin(), perm.end())); 
    }
    for(int d2 = 1; d2 < d1; d2++) { 
      vector<int>arr = {d2, d1 - d2, 180 - d1};
      vector<int>perm = {0, 1, 2}; 
      do { 
        int x_a = d2       + arr[perm[0]]; 
        int x_b = d1 - d2  + arr[perm[1]];
        int x_c = 180 - d1 + arr[perm[2]];  
        if(x_a == x_b && x_b == x_c) { 
         cout << d2 << '\n'; 
         return; 
        }
      }
      while(next_permutation(perm.begin(), perm.end())); 
    }
    return; 
   }
}; 
 
int main(void) { 
  Pizza problem; 
  problem.solve(); 
  return 0; 
}