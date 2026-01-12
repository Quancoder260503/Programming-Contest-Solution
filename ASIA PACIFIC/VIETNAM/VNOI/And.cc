#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())

class And { 
 public :
  /* 
  bool check(vector<int>&a) { 
   vector<vector<int>>sum_and(sz(a), vector<int>(sz(a)));
   for(int i = 0; i < sz(a); i++) { 
    sum_and[i][i] = a[i]; 
    for(int j = i + 1; j < sz(a); j++) { 
     sum_and[i][j] = sum_and[i][j - 1] & a[j]; 
    }
   }
   for(int l1 = 0; l1 < sz(a); l1++) { 
    for(int l2 = 0; l2 < sz(a); l2++) { 
     for(int r1 = l1; r1 < sz(a); r1++) { 
      for(int r2 = l2; r2 < sz(a); r2++) { 
        if(l1 == l2 && r1 == r2) continue; 
        if(sum_and[l1][r1] == sum_and[l2][r2]) return false; 
      }
     }
    }
   }
   return true; 
  }
  void rec(vector<int>&a, int curr, int X, int n) { 
    if(curr == n) {
      if(check(a)) { 
       for(auto &x : a) { 
        cout << x << " "; 
       }
       cout << '\n'; 
      }
      return; 
    }
    for(int i = 0; i <= X; i++) { 
      a.push_back(i); 
      rec(a, curr + 1, X, n); 
      a.pop_back(); 
    }
    return; 
  }
  */ 
  void solve() {
   int X; 
   cin >> X; 
   if(X == 1) { 
    cout << 1 << '\n' << 1 << '\n'; 
    return; 
   } 
   int N = 0; 
   while(2 * (1 << N) - 2 <= X) { 
    N++; 
   }
   cout << N << '\n'; 
   for(int i = 0; i < N; i++) { 
    cout << (1 << N) - (1 << i) - 1 << ' '; 
   }
   cout << '\n'; 
   return;  
 } 
}; 
 
int main(void) { 
  And task;  
  int T; 
  for(cin >> T; T--; ) task.solve(); 
  return 0; 
}