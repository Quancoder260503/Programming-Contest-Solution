#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 
const int maxf = 302; 

int64_t dp[maxf][maxf][maxf]; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int R, G, B; 
 cin >> R >> G >> B; 
 vector<int>r(R), g(G), b(B); 
 for(int i = 0; i < R; i++) { 
  cin >> r[i]; 
 }
 for(int i = 0; i < G; i++) { 
  cin >> g[i]; 
 }
 for(int i = 0; i < B; i++) { 
  cin >> b[i]; 
 }
 sort(r.rbegin(), r.rend()); 
 sort(g.rbegin(), g.rend()); 
 sort(b.rbegin(), b.rend()); 
 memset(dp, -1, sizeof(dp)); 
 dp[0][0][0] = 0; 
 int64_t ret = 0; 
 for(int i = 0; i <= R; i++) { 
  for(int j = 0; j <= G; j++) { 
   for(int k = 0; k <= B; k++) { 
    ret = max(ret, dp[i][j][k]); 
    if(dp[i][j][k] < 0) continue;
    if(i < R && j < G) dp[i + 1][j + 1][k] = max(dp[i + 1][j + 1][k], dp[i][j][k] + r[i] * g[j]); 
    if(i < R && k < B) dp[i + 1][j][k + 1] = max(dp[i + 1][j][k + 1], dp[i][j][k] + r[i] * b[k]); 
    if(j < G && k < B) dp[i][j + 1][k + 1] = max(dp[i][j + 1][k + 1], dp[i][j][k] + g[j] * b[k]); 
   }
  }
 }
 cout << ret << '\n'; 
 return 0; 
}