#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <numeric>

using namespace std;

#define ll long long

const int maxn = 1e5 + 10;
const ll oo = 1e16;

ll a[maxn], b[maxn], c[maxn], dp[maxn][22];
int n, r, k, ord[maxn];

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 cin >> r >> n >> k;
 for(int i = 0; i < maxn; i++) {
  for(int j = 0; j < 22; j++) {
   dp[i][j] = -oo;
  }
 }
 dp[0][0] = r;
 for(int i = 1; i <= n; i++) {
  cin >> a[i] >> b[i] >> c[i];
 }
 iota(ord + 1, ord + n + 1, 1);
 sort(ord + 1, ord + n + 1, [&](int i, int j) {
  return a[i] < a[j];
 });
 for(int pos = 0; pos <= n; pos++) {
  for(int j = 0; j <= k; j++) {
   ll &ret = dp[pos][j];
   if(pos > 0) ret = max(ret, dp[pos - 1][j]);
   if(j   > 0) ret = max(ret, dp[pos][j - 1] * 2);
   if(pos > 0 && dp[pos - 1][j] >= a[ord[pos]] && b[ord[pos]] >= a[ord[pos]]) {
    ll curr = dp[pos - 1][j] + (b[ord[pos]] - a[ord[pos]]) * c[ord[pos]];
    ret = max(ret, curr);
   }
  }
 }
 cout << dp[n][k] << '\n';
 return 0;
}

