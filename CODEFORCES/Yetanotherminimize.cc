#include "bits/stdc++.h"

using namespace std;

int dp[102][100002]; 

void solve() { 
 int N; 
 cin >> N; 
 vector<int>a(N + 1), b(N + 1), total(N + 1); 
 for(int i = 1; i <= N; i++) { 
  cin >> a[i]; 
 }
 for(int i = 1; i <= N; i++) { 
  cin >> b[i]; 
 }
 for(int i = 1; i <= N; i++) { 
  total[i] = total[i - 1] + a[i] + b[i]; 
 }
 memset(dp, -1, sizeof(dp)); 
 dp[0][0] = 0; 
 for(int i = 1; i <= N; i++) { 
  for(int weight = 0; weight <= total[i - 1]; weight++) { 
   if(dp[i - 1][weight] == -1) continue; 
   if(weight + a[i] < 10002) { 
    int cost = 2 * a[i] * weight + 2 * (total[i - 1] - weight) * b[i] + dp[i - 1][weight]; 
    if(dp[i][weight + a[i]] == -1) dp[i][weight + a[i]] = cost; 
    else { 
      dp[i][weight + a[i]] = min(dp[i][weight + a[i]], cost); 
    }
   }
   if(weight + b[i] < 10002) { 
    int cost = 2 * b[i] * weight + 2 * (total[i - 1] - weight) * a[i] + dp[i - 1][weight]; 
    if(dp[i][weight + b[i]] == -1) dp[i][weight + b[i]] = cost; 
    else { 
      dp[i][weight + b[i]] = min(dp[i][weight + b[i]], cost); 
    }
   }
  }
 }
 //cout << dp[3][12] << " " << total[3] << '\n'; 
 int ret = int(1e9); 
 for(int weight = 0; weight < 10002; weight++) { 
  if(dp[N][weight] == -1) continue; 
  ret = min(ret, dp[N][weight]); 
 }
 for(int i = 1; i <= N; i++) { 
  ret += (N - 1) * (a[i] * a[i] + b[i] * b[i]); 
 }
 cout << ret << '\n'; 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int T; 
  for(cin >> T; T--; ) { solve();  }
  return 0; 
}
/**
 * (a[i] + a[j]) ^ 2= a[i] ^ 2 + 2 * a[i] * a[j] + a[j] ^ 2 
 * 
 */