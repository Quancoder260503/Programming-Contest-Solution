#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

#define ll unsigned long long
#define sz(x) int(x.size())

int main(void) {
 int n;
 ll x, y, r, c;
 cin >> n >> r >> c;
 set<ll>rows, cols;
 for(int i = 0; i < n; i++) {
  cin >> x >> y;
  rows.insert(x);
  cols.insert(y);
 }
 ll ans = c * sz(rows) + (r - sz(rows)) * sz(cols);
 cout << ans << '\n';
 return 0;
}

