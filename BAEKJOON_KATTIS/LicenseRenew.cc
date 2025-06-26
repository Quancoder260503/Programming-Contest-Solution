#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define ctoi(x) x - 'a'

const int MOD = 998244353; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 int N, S1, S2; 
 cin >> N >> S1 >> S2; 
 vector<int>arr(N); 
 for(int i = 0; i < N; i++) { 
  cin >> arr[i]; 
 }
 if(S1 > S2) swap(S1, S2); 
 vector<vector<int>>dp(N + 1, vector<int>(S1 + 1, -1)); 
 dp[0][S1] = S2; 
 for(int i = 0; i < N; i++) { 
  for(int w = 0; w <= S1; w++) { 
   if(dp[i][w] >= arr[i]) { 
    dp[i + 1][w] = max(dp[i + 1][w], dp[i][w] - arr[i]); 
   } 
   if(w + arr[i] <= S1)  { 
    dp[i + 1][w] = max(dp[i + 1][w], dp[i][w + arr[i]]); 
   }
  }
 }
 int ans = 0, ind; 
 for(ind = 1; ind <= N; ind++) { 
  int cango = false; 
  for(int w = 0; w <= S1; w++) { 
   if(dp[ind][w] >= 0) { 
    cango = true;
    break;
   }
  }
  if(!cango) { 
    break; 
  }
 }
 ind--; 
 cout << ind << '\n'; 
 return 0; 
}