#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxn = 302;
const int MOD = 1e9 + 7;

#define ll long long

ll dp[maxn][maxn], Comb[maxn][maxn];
int vis[maxn];

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  Comb[0][0] = 1;
  for(int i = 1; i < maxn; i++) {
   for(int j = 0; j <= i; j++) {
    Comb[i][j] = (Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0)) % MOD;
   }
  }
  int n;
  cin >> n;
  vector<vector<int>>mat(n, vector<int>(n));
  for(int i = 0; i < n; i++) {
   for(int j = 0; j < n; j++) {
    cin >> mat[i][j];
    mat[i][j]--;
   }
  }
  vector<int>colour;
  for(int c = 0; c < n; c++) {
   for(int i = 0; i < n; i++) if(!vis[i]) {
    int cnt = 0, color = -1;
    for(int j = 0; j < n; j++) {
     if(!vis[j] && i != j && (color == -1 || color == mat[i][j])) {
      cnt++;
      color = mat[i][j];
     }
    }
    if(cnt == n - c - 1) {
    // cout << i << " " << color << '\n';
     colour.push_back(color);
     vis[i] = true;
    }
   }
  }
  //for(auto &x : colour) cout << x << '\n';
  for(int i = 0; i < maxn; i++)
  for(int j = 0; j < maxn; j++) {
   dp[i][j] = 1;
  }
  ll ret = n;
  for(int c = 2; c <= n; c++) {
   vector<vector<ll>>suffix(maxn, vector<ll>(n));
   fill(suffix.back().begin(), suffix.back().end(), 1);
   for(int i = sz(suffix) - 2; i >= 0; i--) {
    for(int j = 0; j < n; j++) {
     suffix[i][j] = (suffix[i + 1][j] * dp[i + 1][j]) % MOD; // size is at most (c - 1)
    }
   }
   vector<ll>prefix(n, 1);
   for(int i = 0; i < maxn; i++) {
    int cnt = 0;
    for(int j = 0; j < n; j++) {
     (ret += 1LL * c % MOD * Comb[cnt][c - 1] % MOD * prefix[j] % MOD * suffix[i][j] % MOD) %= MOD;
     (dp[i][j] += Comb[cnt][c - 1]) %= MOD;
     prefix[j] = (prefix[j] * dp[i][j]) % MOD;
     cnt += (colour[j] == i);
    }
   }
  }
  cout << ret << '\n';
  return 0;
}
