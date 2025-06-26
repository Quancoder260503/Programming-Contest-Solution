#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 752;
const int mod = 1e9 + 7;

int64_t dyn[maxf][maxf], ways[maxf][maxf], ctr[maxf][maxf], a[26][26], g[maxf][maxf];
string S;
int N, A;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> A >> S;
  S = " " + S;
  for (int i = 0; i < A; i++) {
    for (int j = 0; j < A; j++) {
      cin >> a[i][j];
    }
  }
  for(int i = 1; i <= N; i++) { 
    for(int j = 1; j <= N; j++) { 
      g[i][j] = a[S[i] - 'A'][S[j] - 'A'];
    }
  }
  for (int i = N; i > 0; i--) {
    dyn[i][i + 1] = g[i][i + 1];
    for (int j = i + 2; j <= N; j++) {
      for (int k = i + 1; k < j; k++) {
        (dyn[i][j] += g[i][k] % mod * (k == i + 1 ? 1 : dyn[i + 1][k - 1]) % mod * dyn[k + 1][j] % mod) %= mod; 
      }
      (dyn[i][j] += g[i][j] % mod * dyn[i + 1][j - 1] % mod) %= mod; 
    }
  } 
  ways[1][N] = 1;
  for(int Left = 1; Left <= N; Left++) { 
    for(int j = 1; j <= N; j++) { 
      for(int Right = j + 1; Right <= N; Right++) { 
        int64_t cc = dyn[1][Left - 1] % mod * dyn[Right + 1][N] % mod;
        if(Left == 1)  (cc += dyn[Right + 1][N] % mod) %= mod; 
        if(Right == N) (cc += dyn[1][Left - 1] % mod)  %= mod;  
        ctr[j][Left] += (Right == j + 1 ? 1 : dyn[j + 1][Right - 1]) % mod * (ways[Left][Right] + cc) % mod * g[Left][Right] % mod; 
        ctr[j][Left] %= mod; 
      }
    }
    for(int i = Left + 1; i <= N; i++) { 
      for(int j = N; j > i; j--) { 
        if(i == 1 && j == N) continue; 
        (ways[i][j] += (Left + 1 == i ? 1 : dyn[Left + 1][i - 1]) % mod * ctr[j][Left] % mod) %= mod; 
      }
    }
  }
  for(int i = 1; i <= N; i++) { 
    for(int j = i + 1; j <= N; j++) { 
      if(i == 1 && j == N) continue; 
      (ways[i][j] += dyn[1][i - 1] % mod * dyn[j + 1][N] % mod) %= mod; 
      if(i == 1) (ways[i][j] += dyn[j + 1][N] % mod) %= mod; 
      if(j == N) (ways[i][j] += dyn[1][i - 1] % mod) %= mod; 
    }
  }
  for (int i = 1; i <= N; i++) {
    for (int ch = 0; ch < A; ch++) {
      int64_t ret = dyn[1][N];
      for (int j = i + 1; j <= N; j++) {
        ret = (ret - ways[i][j] % mod * (i + 1 == j ? 1 : dyn[i + 1][j - 1]) % mod * g[i][j] % mod + mod) % mod;
        ret = (ret + ways[i][j] % mod * (i + 1 == j ? 1 : dyn[i + 1][j - 1]) % mod * a[ch][S[j] - 'A'] % mod + mod) % mod;
      }
      for(int j = 1; j < i; j++) { 
        ret = (ret - ways[j][i] % mod * (i == j + 1 ? 1 : dyn[j + 1][i - 1]) % mod * g[j][i] % mod + mod) % mod;
        ret = (ret + ways[j][i] % mod * (i == j + 1 ? 1 : dyn[j + 1][i - 1]) % mod * a[S[j] - 'A'][ch] % mod + mod) % mod;
      }
      cout << ret << '\n'; 
    }
  } 
  return 0;
}