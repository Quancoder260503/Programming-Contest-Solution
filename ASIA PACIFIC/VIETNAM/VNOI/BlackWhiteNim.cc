#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_set>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <unordered_map>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

using namespace std;

#define sz(x) int(x.size())
#define double long double

using VD = vector<double>;

const int maxn = 1 << 7;
const int maxf = 105;


double dp[maxn][maxn][maxn][3];   // ways to achieve(total_ball, num_black_so_far) dp[total_bal][num_black_so_far][curr_grundy_value][colour_of_the_last stones]

int main(void) {
 ios::sync_with_stdio(false); 
 cin.tie(0);
 cout.tie(0);
 dp[0][0][maxf - 1][1] = 1.;
 for(int whites = 0; whites < maxf; whites++) {
  for(int blacks = 0; blacks < maxf; blacks++) {
   double prob = 1., den = blacks + whites;
   for(int last_whites = whites - 1; last_whites >= 0; last_whites--, den--) {
    int stones_packed = whites - last_whites;
    prob = prob * (last_whites + 1) / den;
    for(int curr_grundy = 0; curr_grundy < maxf; curr_grundy++) {
     double &ret = dp[whites][blacks][stones_packed + (stones_packed >= curr_grundy)][0];
     ret += dp[last_whites][blacks][curr_grundy][1] * prob;
    }
    dp[whites][blacks][stones_packed + 1][0] += prob * (dp[last_whites][blacks][1][2] + dp[last_whites][blacks][0][2]);
   }
   if(blacks > 0) {
    prob = 1. * blacks / (whites + blacks);
    for(int curr_grundy = 0; curr_grundy < maxf; curr_grundy++) {
     dp[whites][blacks][curr_grundy][1] += dp[whites][blacks - 1][curr_grundy][0] * prob;
     if(curr_grundy > 0) dp[whites][blacks][1][2] += dp[whites][blacks - 1][curr_grundy][1] * prob;
    }
    dp[whites][blacks][0][2] += dp[whites][blacks - 1][1][2] * prob;
    dp[whites][blacks][1][2] += dp[whites][blacks - 1][0][2] * prob;
   }
  }
 }
 cout << fixed << setprecision(7);
 int C;
 cin >> C;
 for(int case_id = 0, n; case_id < C; case_id++) {
  cin >> n;
  vector<int>black(n), white(n);
  for(auto &x : black) cin >> x;
  for(auto &x : white) cin >> x;
  vector<double>dyn(maxn);
  dyn[0] = 1;
  for(int i = 0; i < n; i++) {
   vector<double>ndyn(maxn);
   int num_black = black[i], num_white = white[i];
   vector<double>cnt(maxn);
   for(int c = 0; c < maxn; c++) {
    cnt[c] += dp[num_white][num_black][c][0] + dp[num_white][num_black][c][2];
    cnt[0] += dp[num_white][num_black][c][1];
   }
   for(int c = 0; c < maxn; c++) {
    for(int j = 0; j < maxn; j++) {
     ndyn[c ^ j] += dyn[c] * cnt[j];
    }
   }
   dyn.swap(ndyn);
  }
  cout << 1. - dyn[0] << '\n';
 }
 return 0;
}

