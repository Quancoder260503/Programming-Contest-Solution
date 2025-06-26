#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define mp make_pair

const int64_t oo = 1e16; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int N, K; 
 cin >> N >> K; 
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 auto check = [&](int64_t amt) { 
  pair<int64_t, int>dp[N][2];
  dp[0][0] = mp(0, 0);  
  dp[0][1] = mp(a[0] - amt, 1); 
  for(int i = 1; i < N; i++) { 
   dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]); 
   dp[i][1] = max(mp(dp[i - 1][0].first + a[i] - amt, dp[i - 1][0].second + 1), 
                  mp(dp[i - 1][1].first + a[i], dp[i - 1][1].second));
  }
  return max(dp[N - 1][1], dp[N - 1][0]); 
 }; 
 int64_t lo = 0, hi = oo; 
 while(lo < hi) { 
  int64_t mid = (lo + hi + 1) / 2; 
  check(mid).second >= K ? lo = mid : hi = mid - 1; 
 }
 auto [c, d] = check(lo); 
 cout << c + d * lo << '\n'; 
 return 0;
}
