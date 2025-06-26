#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1048580;
long long n, L;
long long A[N];
long long dp[N];
long long cnt[N];
bool vis[N];
vector<pair<long long, long long>> subset(const vector<int>& A) {
  vector<pair<long long, long long>> ans;
  int n = A.size();
  for (int mask = 0; mask < (1ll << n); mask++) {
    for (int i = mask;; i = (i - 1) & mask) {
      long long sum = 0;
      for (int j = 0; j < n; j++) {
        if ((1ll << j) & i) {
          sum = sum - A[j];
        } else if ((1ll << j) & mask) {
          sum = sum + A[j];
        }
      }
      if (sum >= 0) ans.push_back({sum, mask});
      if (i == 0) break;
    }
  }
  sort(ans.begin(), ans.end());
  ans.erase(unique(ans.begin(), ans.end()), ans.end());
  return ans;
}
signed main() {
  cin >> n;
  vector<int> left, right;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (i < n / 2)
      left.push_back(x);
    else
      right.push_back(x);
  }
  vector<pair<long long, long long>> lf = subset(left);
  vector<pair<long long, long long>> rt = subset(right);
  int s, e;
  s = e = 0;
  while (s < lf.size() && e < rt.size()) {
    if (s < lf.size() && lf[s].first < rt[e].first)
      s++;
    else if (e < rt.size() && lf[s].first > rt[e].first)
      e++;
    else {
      int s0 = s;
      int e0 = e;
      while (s0 < lf.size() && lf[s].first == lf[s0].first) s0++;
      while (e0 < rt.size() && rt[e].first == rt[e0].first) e0++;
      for (int i = s; i < s0; i++) {
        for (int j = e; j < e0; j++) {
          vis[lf[i].second | (rt[j].second << left.size())] = 1;
        }
      }
      s = s0;
      e = e0;
    }
  }
  long long ans = 0;
  for (int mask = 1; mask < (1ll << n); mask++) {
    ans += vis[mask];
  }
  cout << ans << endl;
  return 0;
}