#include "bits/stdc++.h"

using namespace std;

using ll = long long;

int dp[30][3002];

int row_period[26] = {
 0, 0, 3, 3, 6, 12, 24, 12, 24, 24, 24, 24, 48,  48, 96, 96, 96, 192, 192, 384, 384, 384, 768, 768, 768, 768
};
int row_preperiod[26] = {
 0, 0, 4, 4, 15, 22, 52, 50, 117, 127, 152, 249, 326, 396, 479, 710, 790, 964, 1058, 1304, 1417, 1550, 2021, 2062, 2142, 2501
};

int main() {
 //memset(dp, -1, sizeof dp);
 for(int r = 1; r < 26; r++) {
  multiset<int>ms;
  int mex = 0;
  for(int c = 1; c < 3000; c++) {
   int old_mex = mex;
   for(int j = 1; j < r; j++) ms.insert(dp[j][c]);
   for(int j = 1; j < min(r, c); j++) ms.insert(dp[r - j][c - j]);
   //int mex = 0;
   while(ms.count(mex)) mex++;
   dp[r][c] = mex;
   ms.insert(dp[r][c]);
   for(int j = 1; j < r; j++) ms.erase(ms.find(dp[j][c]));
   for(int j = 1; j < min(r, c); j++) ms.erase(ms.find(dp[r - j][c - j]));
   mex = old_mex;
   while(ms.count(mex)) mex++;
  }
 }
 auto grundy = [&](int r, int c) { return dp[r][c]; };
 int tc;
 for(cin >> tc; tc--; ) {
  ll r, c, R, C;
  int n;
  cin >> R >> C >> n;
  ll grundy_sum = 0;
  for(int i = 0; i < n; i++) {
   cin >> r >> c;
   if(r == 1) {
    grundy_sum = grundy_sum ^ (c - 1);
   }
   else {
    if(c < 1LL * row_preperiod[r]) {
      grundy_sum = grundy_sum ^ grundy(r, c);
    } else {
     ll start = 1LL * (row_preperiod[r] - row_period[r]) + (c - row_preperiod[r] + row_period[r]) % row_period[r];
     grundy_sum = grundy_sum ^ (1LL * grundy(r, start) + (c - row_preperiod[r] + row_period[r]) / row_period[r] * row_period[r]);
    }
   }
  }
  cout << (grundy_sum ? "YES" : "NO") << '\n';
 }
 return 0;
}


