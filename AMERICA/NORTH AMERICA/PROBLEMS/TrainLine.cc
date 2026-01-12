#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <climits> 
#include <cmath>
#include <numeric> 
#include <iomanip> 
#include <utility>

using namespace std;

const double oo = 1e9;
const int WINDOW = 50;

int main(void) {
 int n, k;
 cin >> n >> k;
 vector<int>P(n), D(n);
 vector<double>inv_two{1.0};
 for(int i = 0; i < n; i++) {
  cin >> P[i] >> D[i];
 }
 for(int i = 0; i < 2 * WINDOW; i++)  {
  inv_two.push_back(inv_two.back() / 2.);
 }
 vector<vector<double>>cc(n, vector<double>(WINDOW));
 for(int i = 0; i < n; i++) {
  for(int j = 0; j < WINDOW; j++) {
   for(int k = max(0, i - WINDOW); k < min(n, i + WINDOW); k++) {
    if(D[k] >= D[i] - j / 2) {
     cc[i][j] += P[k] * (inv_two[min(2 * WINDOW, abs(D[i] - D[k]))] -
                         inv_two[min(2 * WINDOW, abs(D[i] - D[k] - j))]);
   //  cerr << cc[i][j] << '\n';
    }
   }
  }
 }
 double lo = 0, hi = 1000.0, lambda;
 pair<double, int>ret;
 while(hi - lo > 1e-9){
  lambda = (lo + hi) / 2;
  vector<pair<double, int>>dp(WINDOW);
  for(int i = 0; i < n; i++) {
   pair<double, int>nxt{0, 0};
   for(int j = WINDOW - 1; j >= 0; j--) {
    int d = min(WINDOW - 1, j + D[i] - (i ? D[i - 1] : -1000000));
    double v = dp[j].first + cc[i][d] - lambda;
    //cout << v << " " << cc[i][d] << '\n';
    if(v > nxt.first) nxt = {v, dp[j].second + 1};
    if(j < WINDOW - 1) {
     dp[d] = max(dp[d], dp[j]);
     dp[j] = {0, 0};
    // cout << dp[d].first << '\n';
    }
   }
   dp[0] = nxt;
  }
  ret = {0, 0};
  for(auto const &x : dp) ret = max(ret, x);
  (ret.second > k ? lo = lambda : hi = lambda);
 }
 cout << fixed << setprecision(10) << ret.first + k * lambda << '\n';
 return 0;
}
