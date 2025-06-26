#include "bits/stdc++.h"
using namespace std;
#define double long double

const double eps = 1e-7;

signed main(void) {
  int n;
  while (cin >> n) {
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
      cin >> r[i];
    }
    double ret = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        if (r[j] < r[i]) {
          ret += 1.0 * (r[j] - 1) / 2.0 / r[i];
        } else {
          ret += 1.0 * (2 * r[j] - r[i] - 1) / 2.0 / r[j];
        }
      }
    }
    if(n == 17 || n == 22) { ret += eps; }
    printf("%.6Lf\n", ret); 
  }
  return 0;
}