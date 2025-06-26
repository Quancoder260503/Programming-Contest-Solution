#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int N = 1e5 + 10;
const int M = 110;
const long long INF = 1e17;
long long n, k;
long long dp[N + 1][M + 1];
long long a[N + 1];
signed main(void) {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) cin >> a[i];
  memset(dp, 0x3f3f3f3f, sizeof(dp));
  dp[0][1] = 0;
  for (int i = 1; i <= n; i++) dp[i][1] = max(dp[i - 1][1], a[i]);
  for (int i = 2; i <= k; i++) {
    stack<pair<long long, int>> stk;
    for (int j = i; j <= n; j++) {
      long long mn = dp[j - 1][i - 1];
      while (stk.size() && a[stk.top().second] <= a[j]) {
        mn = min(mn, stk.top().first);
        stk.pop();
      }
      dp[j][i] = min(dp[stk.size() ? stk.top().second : 0][i], mn + a[j]);
      stk.push({mn, j});
    }
  }
  cout << dp[n][k] << endl;
  return 0;
}