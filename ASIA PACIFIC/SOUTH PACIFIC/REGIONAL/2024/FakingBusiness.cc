#include "bits/stdc++.h"

using namespace std;  

const int MOD = 1e9 + 7; 

#define ll long long 
#define sz(x) int(x.size()) 

ll dp[500][500], a[500], prefix[500]; 

const ll oo = 1e15; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n; 
 cin >> n;
 for(int i = 1; i <= n; i++) { 
  cin >> a[i]; 
  prefix[i] = prefix[i - 1] + a[i]; 
 }
 memset(dp, 63, sizeof dp);  
 for(int i = 1; i <= n; i++) { 
  dp[i][1] = prefix[i]; 
 }
 for(int c = 2; c <= n; c++) { 
  for(int i = 1; i <= n; i++) { 
   for(int j = 1; j <= i; j++) { 
    if((prefix[i] - prefix[j - 1]) > dp[j - 1][c - 1]) { 
     dp[i][c] = min(dp[i][c], prefix[i] - prefix[j - 1]); 
    }
   }  
  }
 }
 for(int i = n; i > 0; i--) { 
  if(dp[n][i] < oo) { 
   cout << i << '\n'; 
   break; 
  }  
 }
 return 0; 
}