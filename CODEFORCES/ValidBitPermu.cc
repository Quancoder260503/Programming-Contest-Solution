#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int MOD = 1e9 + 7;
 
void solve() {
 int N, first_pos, second_pos, x, y;
 cin >> N >> first_pos >> second_pos >> x >> y;
 vector<vector<int64_t>> Comb(N + 1, vector<int64_t>(N + 1));
 Comb[0][0] = 1;
 for (int i = 1; i < sz(Comb); i++) {
  for (int j = 0; j <= i; j++) {
   Comb[i][j] = (Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0)) % MOD;
  }
 }
 if (x == N) { 
  cout << (first_pos == 1 ? 0 : Comb[N - y - 1][second_pos - first_pos - 1] % MOD * Comb[y - 1][N - second_pos] % MOD) << '\n'; 
 } else if(y == N) { 
  cout << (second_pos == N ? 0 : Comb[N - x - 1][second_pos - first_pos - 1] % MOD * Comb[x - 1][first_pos - 1] % MOD) << '\n'; 
 }
 else if (x < y) {
  int64_t ans = 0;
  int rem = first_pos - 1 + N - second_pos - (x - 1);
  if (rem >= 0) {
   int64_t c = Comb[x - 1][first_pos - 1] % MOD * Comb[y - x - 1][rem] % MOD;
   int amt = y - x - 1 - rem;
   rem = N - second_pos - rem;
   for (int pos = first_pos + 1; pos < second_pos; pos++) {
    if (pos - first_pos > amt) {
     (ans += c % MOD * Comb[N - y - 1][pos - first_pos - 1 - amt] % MOD) %= MOD;
    }
   }
  }
  // Max on the right;
  for (int right = second_pos + 1; right < N; right++) {
   (ans += Comb[x - 1][first_pos - 1] % MOD *
           Comb[y - x - 1][second_pos - first_pos - 1] % MOD *
           Comb[N - y - 1][right - second_pos - 1] % MOD) %= MOD;
  }
  cout << ans << '\n';
 } else {
  int64_t ans = 0;
  int rem = first_pos - 1 + N - second_pos - (y - 1);
  if (rem >= 0) { 
   int64_t c = Comb[y - 1][N - second_pos] % MOD * Comb[x - y - 1][rem] % MOD;
   //cout << Comb[x - y - 1][rem] << '\n'; 
   int amt = x - y - 1 - rem;
   rem = first_pos - 1 - rem;
   for (int pos = second_pos - 1; pos > first_pos; pos--) {
    if (second_pos - pos > amt) {
     (ans += c % MOD * Comb[N - x - 1][second_pos - pos - 1 - amt] % MOD) %= MOD;
    }
   }
  }
  // Max on the left;
  for (int left = first_pos - 1; left > 1; left--) {
   (ans += Comb[y - 1][N - second_pos] % MOD *
           Comb[x - y - 1][second_pos - first_pos - 1] % MOD *
           Comb[N - x - 1][first_pos - left - 1] % MOD) %= MOD;
  }
  cout << ans << '\n';
 }
 return;
}
 
int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int T;
 for (cin >> T; T--;) {
  solve();
 }
 return 0;
}