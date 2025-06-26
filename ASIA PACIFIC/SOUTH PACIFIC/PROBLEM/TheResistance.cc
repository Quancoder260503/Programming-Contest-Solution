#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

double Comb[20][20];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  Comb[0][0] = 1;
  for (int i = 1; i < 20; i++) {
    for (int j = 0; j <= i; j++) {
      Comb[i][j] = Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0);
    }
  }
  int N, S, M, Q;
  while (cin >> N >> S >> M >> Q && N) {
    vector<int> c(M), f(M);
    for (int i = 0; i < M; i++) {
      cin >> c[i];
    }
    for (int i = 0; i < M; i++) {
      cin >> f[i];
    }
    vector<vector<int>> games(M);
    for (int i = 0; i < M; i++) {
      games[i].resize(c[i]);
      for (int j = 0; j < sz(games[i]); j++) {
        cin >> games[i][j];
        games[i][j]--;
      }
    }
    double ret = 0, den = 0; 
    vector<double>Prob((1 << N)); 
    for (int mask = 0; mask < (1 << N); mask++) {
      if (__builtin_popcount(mask) != S) continue;
      int flag = true;
      for (int i = 0; i < M; i++) {
        int cc = 0;
        for (auto &v : games[i]) {
          cc += (mask >> v) & 1;
        }
        flag &= (cc >= f[i]);
      }
      if (!flag) continue; 
      double p = 1; 
      for (int i = 0; i < M; i++) {
        int cc = 0;
        for (auto &v : games[i]) {
          cc += (mask >> v) & 1;
        }
        p = p * Comb[cc][f[i]] * pow(0.5, cc - f[i]);
      } 
      Prob[mask] = p;
      den += Prob[mask]; 
    }
    for(int mask = 0; mask < (1 << N); mask++) { 
      Prob[mask] /= den; 
    }
    int pN = (1 << N) - 1; 
    for(int mask = pN; mask >= 0; mask--) { 
      for(int pmask = mask; pmask; pmask = (pmask - 1) & mask) {
        if(mask != pmask) Prob[mask] += Prob[pmask]; 
      }  
    }
    ret = 0; 
    for(int mask = 0; mask < (1 << N); mask++) { 
      if(__builtin_popcount(mask) != Q) continue; 
      ret = max(ret, Prob[mask ^ pN]); 
    }
    cout << fixed << setprecision(5) << ret << '\n';
  }
  return 0;
}