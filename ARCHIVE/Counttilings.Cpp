#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N = (1 << 20) + 10;
const int M = 21;
const long long INF = 1e17; 
const int mod = 1e9 + 7;
int A[N];
long long dp[2][N];
int n,m; 
int cost[M][M]; 
int main(){
      cin >> n >> m; 
      dp[0][0] = 1;
      for(int j = 0; j < m; j++){
           for(int i = 0; i < n; i++){
                for(int mask = 0; mask < (1 << n); mask++){
                      dp[1][mask] = dp[0][mask xor (1 << i)]; 
                      if(i && !((1 << i) & mask) && !((1 << (i - 1)) & mask)){
                           dp[1][mask] = (dp[1][mask] + dp[0][mask xor (1 << (i - 1))] + mod) % mod; 
                      }
                }
                for(int mask = 0; mask < (1 << n); mask++){
                      dp[0][mask] = dp[1][mask]; 
                }
           }
      }
      cout << dp[0][0] << endl; 
      return 0; 
}