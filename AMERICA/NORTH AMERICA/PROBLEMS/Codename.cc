#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

double dp[(1 << 15) + 1][2][22][52];

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int n, m;
 char team;
 cin >> n >> team;
 int mask_a = 0, mask_b = 0, assassin = 0;
 vector<string>words(n);
 map<string, int>mp;
 string types(n, '0');
 for(int i = 0; i < n; i++) {
  cin >> words[i];
  mp[words[i]] = i;
 }
 for(int i = 0; i < n; i++) {
  cin >> types[i];
  if(types[i] == 'R') mask_a   |= (1 << i);
  if(types[i] == 'B') mask_b   |= (1 << i);
  if(types[i] == 'A') assassin |= (1 << i);
 }
 if(team == 'B') {
  team = 'R';
  swap(mask_a, mask_b);
  for(int i = 0; i < n; i++) {
   if(types[i] == 'B')      types[i] = 'R';
   else if(types[i] == 'R') types[i] = 'B';
  }
 }
 for(int i = 0; i < (1 << 15) + 1; i++) {
  for(int j = 0; j < 22; j++) {
   for(int k = 0; k < 52; k++) {
    dp[i][0][j][k] = dp[i][1][j][k] = -1.0;
   }
  }
 }
 cin >> m;
 vector<vector<string>>hints(m);
 for(int i = 0, nums; i < m; i++) {
  cin >> nums;
  hints[i].resize(nums);
  for(int j = 0; j < nums; j++) cin >> hints[i][j];
 }
 cout << fixed << setprecision(10);
 function<double(int, int, int, int)> memo = [&](int mask, int who, int num_guesses, int index) -> double {
  if((mask & mask_a) == mask_a) return (who == 0);
  if((mask & mask_b) == mask_b) return (who == 1);
  if(dp[mask][who][num_guesses][index] >= 0.) return dp[mask][who][num_guesses][index];
  double &ret = dp[mask][who][num_guesses][index];
  ret = 0;
  if(num_guesses == 0) {
   for(int i = 0; i < sz(hints); i++) {
    int cnt = 0;
    for(int j = 0; j < sz(hints[i]); j++) {
     int id = mp[hints[i][j]];
     cnt += !(mask >> id & 1);
    }
    if(cnt == 0) continue;
    for(int j = 1; j <= cnt; j++) {
     ret = max(ret, memo(mask, who, j, i));
    }
   }
   //cout << ret << '\n';
  } else {
   double den = 0.;
   for(int j = 0; j < sz(hints[index]); j++) {
    int id = mp[hints[index][j]];
    if(mask >> id & 1) continue;
    den++;
    if(types[id] == (who ? 'B' : 'R')) {
     if(num_guesses > 1) {
      ret += memo(mask | (1 << id), who, num_guesses - 1, index);
     } else {
      ret += 1. - memo(mask | (1 << id), who ^ 1, 0, 0);
     }
    } else if(types[id] != 'A') {
     ret += 1. - memo(mask | (1 << id), who ^ 1, 0, 0);
    }
   }
   ret /= den;
  }
  return ret;
 };
 cout << memo(0, 0, 0, 0) << '\n';
 return 0;
}
