#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#define blksz 500
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e3 + 10;
const long long INF = 1e7 + 5;
const int mod = 1e9 + 7;
long long n, m, k, q, p;
vector<int> adj[N + 1];
long long dp[N + 1][N + 1];
long long pf[N + 1];
bool comp(long long value) {
  memset(dp, false, sizeof(dp));
  dp[0][0] = true;
  for (int t = 1; t <= k; t++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < i; j++) {
        long long cur = pf[i] - pf[j];
        if ((cur & value) == value) {
          dp[i][t] |= dp[j][t - 1];
        }
      }
    }
  }
  return dp[n][k];
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    long long x;
    scanf("%lld", &x);
    pf[i] = pf[i - 1] + x;
  }
  long long ans = 0;
  for (int i = 55; i >= 0; i--) {
    if (comp(ans | (1ll << i))) {
      ans = ans | (1ll << i);
    }
  }
  printf("%lld\n", ans);
  return 0;
}