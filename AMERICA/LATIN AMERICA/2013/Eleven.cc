#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int mod = 1e9 + 7;
const int maxf = 102;

int64_t dyn[10][11][11][maxf][maxf];

int64_t Comb(int a, int b) {
#define COMB_MAXA 5000
#define COMB_MAXB 5000
  static int64_t combmemo[COMB_MAXA + 1][COMB_MAXB + 1];
  if (a < b || b < 0) return 0;
  if (!a) return 1;
  int64_t &ret = combmemo[a][b];
  if (!ret) ret = (Comb(a - 1, b - 1) + Comb(a - 1, b)) % mod;
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string S;
  cin >> S;
  vector<int> c(10);
  for (int i = 0; i < S.size(); i++) {
    c[S[i] - '0']++;
  }
  int N = S.size();
  int even = sz(S) / 2, odd = sz(S) - even;
  for (int sloteven = 0; sloteven <= c[0]; sloteven++) {
    dyn[0][0][0][sloteven][c[0] - sloteven] =
        Comb(even, sloteven) % mod * Comb(odd - 1, c[0] - sloteven) % mod;
  }
  for (int digit = 1; digit < 10; digit++)
    for (int mA = 0; mA < 11; mA++)
      for (int mB = 0; mB < 11; mB++)
        for (int cA = 0; cA <= even; cA++)
          for (int cB = 0; cB <= odd; cB++)
            for (int sloteven = 0; sloteven <= c[digit]; sloteven++) {
              int nA = (mA + sloteven * digit) % 11;
              int nB = (mB + (c[digit] - sloteven) * digit) % 11;
              int kA = cA + sloteven;
              int kB = cB + c[digit] - sloteven;
              if (kA <= even && kB <= odd) {
                dyn[digit][nA][nB][kA][kB] +=
                    dyn[digit - 1][mA][mB][cA][cB] % mod *
                    Comb(even - cA, sloteven) % mod *
                    Comb(odd - cB, c[digit] - sloteven) % mod;
                dyn[digit][nA][nB][kA][kB] %= mod;
              }
            }
  int64_t ret = 0;
  for (int mA = 0; mA < 11; mA++)
    for (int mB = 0; mB < 11; mB++)
      if ((mA - mB + 11) % 11 == 0) {
        ret += dyn[9][mA][mB][even][odd];
        ret %= mod;
      }
  cout << ret << '\n';
  return 0;
}