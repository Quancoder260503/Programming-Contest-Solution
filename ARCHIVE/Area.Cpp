#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 1;
#define double long double
const long long INF = 1e14 + 1;
const int bound = 1e6 + 5;
typedef pair<int, int> pii;
int n;
const double eps = 1e-9;
int ri[N];
int lf[N];
pair<int, int> tree[N];
void build(int l, int r, int p) {
  ri[p] = r;
  lf[p] = l;
  if (l == r) return;
  int mid = ((1ll) * (r + l)) >> 1;
  build(l, mid, 2 * p);
  build(mid + 1, r, 2 * p + 1);
}
void add(int p) {
  if (lf[p] == ri[p]) {
    tree[p].first = tree[p].second ? 1 : 0;
  } else {
    tree[p].first =
        (tree[p].second ? (ri[p] - lf[p] + 1)
                        : tree[2 * p + 1].first + tree[2 * p].first);
  }
}
void update(int l, int r, int p, int val) {
  if (r < lf[p] | ri[p] < l) return;
  if (l <= lf[p] && ri[p] <= r) {
    tree[p].second += val;
    add(p);
    return;
  }
  update(l, r, 2 * p, val);
  update(l, r, 2 * p + 1, val);
  add(p);
}
bool cmp(array<int, 4>& a, array<int, 4>& b) {
  return a[1] == b[1] ? a[0] < b[0] : a[1] < b[1];
}
signed main() {
  scanf("%d", &n);
  vector<array<int, 4>> segs;
  for (int i = 1; i <= n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    segs.push_back({1, y1, x1 + 1, x2});
    segs.push_back({-1, y2, x1 + 1, x2});
  }
  long long ans = 0;
  sort(segs.begin(), segs.end(), cmp);
  int last = -bound;
  build(-bound, bound, 1);
  for (int i = 0; i < segs.size(); i++) {
    ans += (1ll) * (segs[i][1] - last) * tree[1].first;
    update(segs[i][2], segs[i][3], 1, segs[i][0]);
    last = segs[i][1];
  }
  cout << ans << endl;
  return 0;
}