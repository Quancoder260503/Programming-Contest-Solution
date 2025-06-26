#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
#define int64_t long long
 
const int64_t oo = 1e14;
 
class SingleHair {
public:
 void solve() {
  int N, M, X;
  cin >> N >> M >> X;
  vector<int64_t> a(M);
  for (int i = 0; i < M; i++) {
   cin >> a[i];
  }
  int64_t ans = 0;
  int n = min(10001, N);
  vector<vector<int64_t>> dp(n + 2, vector<int64_t>(M + 10, -oo));
  dp[0][0] = a[0];
  for (int pos = 1; pos < n; pos++) {
   for (int hair_len = 0; hair_len < M; hair_len++) {
    if (hair_len == M - 1) {
     dp[pos][hair_len] = max(dp[pos][hair_len], dp[pos - 1][hair_len]);
    }
    if(hair_len > 0) dp[pos][hair_len] = max(dp[pos - 1][hair_len - 1] + a[hair_len], dp[pos][hair_len]);
    for (int next_len = 0; next_len <= hair_len; next_len++) {
     dp[pos][next_len] = max(dp[pos - 1][hair_len] + a[next_len] - X, dp[pos][next_len]);
    }
   }
  }
  for (int i = 0; i <= M; i++) {
   ans = max(ans, dp[n - 1][i]);
  }
  if (n == N) {
   cout << ans << '\n';
   return;
  }
  for (int start = 0; start < 10002; start++) {
   for (int i = 0; i < M; i++) {
    int64_t cc = 0; 
    for (int j = i; j < M; j++) {
     int64_t cyc_len = (N - start - 1) / (j - i + 1);
     cc += a[j]; 
     ans = max(ans, dp[start][j] + 1LL * cyc_len * (cc - X)); 
    }
   }
  }
  /* 
  std::random_device rd;  // Get a random seed
  std::mt19937 gen(rd()); // Mersenne Twister generator
  std::uniform_int_distribution<long long> dist(1'000'000'000, 2'000'000'000);
  for(int i = 0; i < 100; i++) { 
   cout << dist(gen) << '\n'; 
  }
  */ 
  cout << ans << '\n'; 
  return;
 }
};
 
int main(void) {
 SingleHair Problem;
 int T;
 for (cin >> T; T--;) {
  Problem.solve();
 }
 return 0;
}