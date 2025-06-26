#include <bits/stdc++.h>

#include <iostream>
#include <vector>
#define blksz 500;
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long double ld;
const int N = 3e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
const double eps = 3e-14;
long long xa, xb, xc, ya, yb, yc, za, zb, zc;
vector<int> adj[N + 1];
vector<int> dv[N + 1];
map<pair<int, int>, int> dp[N + 1];
long long A[N + 1];
signed main() {
  scanf("%d%d%d%d%d%d%d%d%d", &xa, &ya, &za, &xb, &yb, &zb, &xc, &yc, &zc);
  ld xAC = (ld)(xa - xc);
  ld yAC = (ld)(ya - yc);
  ld zAC = (ld)(za - zc);
  ld xAB = (ld)(xa - xb);
  ld yAB = (ld)(ya - yb);
  ld zAB = (ld)(za - zb);
  ld xBC = (ld)(xc - xb);
  ld yBC = (ld)(yc - yb);
  ld zBC = (ld)(zc - zb);
  ld xM = (ld)yAB * zAC - (ld)zAB * yAC;
  ld yM = (ld)zAB * xAC - (ld)zAC * xAB;
  ld zM = (ld)xAB * yAC - (ld)xAC * yAB;
  ld p = (ld)sqrt((ld)(xM * xM + yM * yM + zM * zM));
  ld AB = (ld)sqrt((ld)(xAB * xAB + yAB * yAB + zAB * zAB));
  ld AC = (ld)sqrt((ld)(xAC * xAC + yAC * yAC + zAC * zAC));
  ld BC = (ld)sqrt((ld)(xBC * xBC + yBC * yBC + zBC * zBC));
  if ((ld)AB * AB + (ld)AC * AC <= BC * BC) {
    ld ans = AC;
    cout << setprecision(20) << ans << endl;
    return 0;
  }
  if ((ld)AB * AB + (ld)BC * BC <= AC * AC) {
    ld ans = BC;
    cout << setprecision(20) << ans << endl;
    return 0;
  }
  ld ans = p / AB;
  cout << setprecision(20) << ans << endl;
  return 0;
}