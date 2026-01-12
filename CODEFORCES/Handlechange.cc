#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = 1e12; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 int n, k, l; 
 string s;
 cin >> n >> k >> l >> s; 
 vector<int>a(n); 
 for(int i = 0; i < n; i++) { 
  a[i] = ('a' <= s[i] && s[i] <= 'z'); 
 }
 auto f = [&](int lambda) { 
  vector<pair<int64_t, int64_t>>dp(n + 1, {oo, oo}); 
  dp[0] = {0, 0};
  for(int i = 0; i < n; i++) { 
   if(dp[i + 1] > make_pair(dp[i].first + a[i], dp[i].second)) { 
    dp[i + 1] = make_pair(dp[i].first + a[i], dp[i].second);
   }
   if(dp[min(n, i + l)] > make_pair(dp[i].first + lambda, dp[i].second + 1)) { 
    dp[min(n, i + l)] = make_pair(dp[i].first + lambda, dp[i].second + 1); 
   }
  }
// cout << dp[n].first << " " << dp[n].second << " " << lambda << '\n'; 
  return dp[n];  
 }; 
 int lo = 0, hi = n;
 int res = 0; 
 while(lo <= hi) { 
  int mid = (lo + hi) / 2; 
  if (f(mid).second > k) {
	lo = mid + 1;
	res = mid;
  } else {
	hi = mid - 1;
  }
 }
 auto ret = f(res);
 if(ret.second <= k) { 
  cout << 0 << '\n'; 
  return 0; 
 } 
 ret = f(res + 1); 
 int64_t ans = oo; 
 ans = min(ans, ret.first - lo * k); 
 for(int i = 0; i < n; i++) { 
  a[i] = ('A' <= s[i] && s[i] <= 'Z'); 
 }
 lo = 0, hi = n;
 while (lo <= hi) {
  int mid = (lo + hi) / 2;
  if (f(mid).second > k) {
	lo = mid + 1;
	res = mid;
  } else {
	hi = mid - 1;
  }
 }
 ret = f(res); 
 if(ret.second <= k) { 
  cout << 0 << '\n'; 
  return 0; 
 }
 ret = f(res + 1); 
// cout << ret.first << " " << ret.second << " " << lo << '\n'; 
 ans = min(ans, ret.first - lo * k); 
 cout << ans << '\n';
 return 0;
}
