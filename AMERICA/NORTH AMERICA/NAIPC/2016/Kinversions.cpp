#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005
using cd = complex<double>;
const double PI = acos(-1);
const int mod = 1e9 + 7;
int n, k, m;
char s[MAXN];
void fft(vector<cd> &a, int sz, bool invert) {
  for (int i = 1, mask = 0; i < sz; i++) {
    int bit = sz >> 1;
    for (; mask & bit; bit = bit / 2) {
      mask = mask xor bit;
    }
    mask = mask xor bit;
    if (i < mask) {
      swap(a[i], a[mask]);
    }
  }
  for (int len = 2; len <= sz; len = len * 2) {
    double angle = 2 * PI / len * (invert ? -1 : 1);
    cd wang(cos(angle), sin(angle));
    for (int i = 0; i < sz; i += len) {
      cd w(1);
      for (int j = 0; j < len / 2; j++) {
        cd u = a[i + j];
        cd v = w * a[i + j + len / 2];
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w = w * wang;
      }
    }
  }
  if (invert) {
    for (int i = 0; i < sz; i++) {
      a[i] /= sz;
    }
  }
  return;
}
vector<long long> mul(vector<int> &a, vector<int> &b) {
  vector<cd> A(a.begin(), a.end()), B(b.begin(), b.end());
  int n = 1;
  while (n < A.size() + B.size()) {
    n = n * 2;
  }
  A.resize(n);
  B.resize(n);
  fft(A, (int)A.size(), false);
  fft(B, (int)B.size(), false);
  for (int i = 0; i < n; i++) {
    A[i] *= B[i];
  }
  fft(A, (int)A.size(), true);
  vector<long long> res(n);
  for (int i = 0; i < n; i++) {
    res[i] = 1LL * round(A[i].real());
  }
  return res;
}
signed main(void) {
  scanf(" %s", &s);
  int n = strlen(s);
  vector<int> arra(MAXN), arrb(MAXN);
  for (int i = 0; i < n; i++) {
    if (s[i] == 'B') {
      arrb[n - i - 1] += 1;
    } else {
      arra[i] += 1;
    }
  }
  vector<long long> res = mul(arrb, arra);
  for (int i = n; i < 2 * n - 1; i++) {
    printf("%lld\n", res[i]);
  }
  return 0;
}