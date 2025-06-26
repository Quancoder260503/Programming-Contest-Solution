#include "bits/stdc++.h"
using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9 + 7; 

/**
 * dp[x][y] = {worst optimal when the actual value is in range [x, y) }
 */


class AwkwardAuction { 
public: 
  void solve() { 
   int N, B;
   cin >> N >> B; 
   vector<vector<int>>dp(N + 1, vector<int>(N + 1, -1)); 
   function<int(int, int)> memo = [&](int L, int R) -> int { 
    if(L == R) return L; 
    if(L >  R) return 0; 
    int &ret = dp[L][R]; 
    if(ret != -1) return ret; 
    ret = oo; 
    for(int k = L; k < R; k++) { 
     ret = min(ret, max(memo(L, k - 1) + k, B + memo(k + 1, R))); 
    }
    ret = min(ret, R + memo(L, R - 1)); 
    return ret; 
   };
   cout << memo(1, N) << '\n'; 
   return;  
  }
}; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 AwkwardAuction auction; 
 auction.solve(); 
 return 0; 
}