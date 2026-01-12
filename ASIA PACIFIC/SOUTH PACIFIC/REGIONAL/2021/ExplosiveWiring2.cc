#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <numeric>
#include <climits>
#include <cassert>
#include <set>

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e9;

struct Tree {
 typedef int T;
 static constexpr T unit = -oo;
 T f(T a, T b) { return max(a, b); }
 vector<T>s; int n;
 Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
 void update(int pos, T val) {
  pos += n;
  s[pos] = max(s[pos], val);
  for(; pos /= 2; ) s[pos] = f(s[2 * pos], s[2 * pos + 1]);
 }
 T query(int b, int e) {
  T ra = unit, rb = unit;
  for(b += n, e += n; b < e; b /= 2, e /= 2) {
   if(b % 2) ra = f(ra, s[b++]);
   if(e % 2) rb = f(s[--e], rb);
  }
  return f(ra, rb);
 }
};

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int n;
 cin >> n;
 vector<pair<int, int>>segs(n);
 int max_p = 0;
 for(int i = 0; i < n; i++) {
  cin >> segs[i].first >> segs[i].second;
  max_p = max(segs[i].second, max_p);
 }
 vector<int>inc(n);
 sort(segs.begin(), segs.end());
 multiset<int>ms;
 for(int i = sz(segs) - 1; i >= 0; i--) {
  auto it = ms.upper_bound(segs[i].second);
  inc[i] = (it != ms.begin());
  ms.insert(segs[i].second);
 }
 vector<int>dp(max_p + 1, 0);
 Tree segtree(max_p + 3);
 Tree segtree_(max_p + 3);
 for(int i = 0; i < sz(segs); i++) {
  int opt = segtree_.query(0, segs[i].first);
  dp[segs[i].second] = max(dp[segs[i].second], 2 + segtree.query(segs[i].first, segs[i].second + 1));
  if(inc[i]) {
   dp[segs[i].second] = max(dp[segs[i].second], 2 + max(0, opt));
  }
  segtree_.update(segs[i].second, dp[segs[i].second]);
  segtree.update(segs[i].second, max(opt, dp[segs[i].first - 1]));
 }
 cout << *max_element(dp.begin(), dp.end()) << '\n';
 return 0;
}

// dp[r[i]] = max(dp[r[i]],
