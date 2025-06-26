#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int MOD = 1e9 + 7; 

int dp[1 << 20][77]; 
string S;   
int N; 

int memo(int pos, int mask) { 
  if(pos == N) return (mask > 0 && __builtin_popcount(mask + 1) == 1); 
  int64_t ret = dp[mask][pos]; 
  if(ret != -1) return ret; 
  ret = (mask > 0 && __builtin_popcount(mask + 1) == 1); 
  for(int st = 0; pos + st < N; st++) { 
   int64_t num = 0; 
   for(int j = pos; j < pos + st + 1; j++) { 
     num = 2 * num + (S[j] - '0'); 
   }
   if(num > 20) break;
   if(num == 0) continue; 
   (ret += memo(pos + st + 1, mask | (1 << (num - 1)))) %= MOD; 
  }
  return dp[mask][pos] = ret;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> S; 
  memset(dp, -1, sizeof(dp)); 
  int64_t ret = 0;  
  for(int i = 0; i < N; i++) {
  (ret += memo(i, 0)) %= MOD; 
  }
  cout << ret << '\n'; 
  return 0; 
}
 
 