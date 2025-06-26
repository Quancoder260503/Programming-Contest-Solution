#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

const int mod = 1e9 + 7;

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res * tmp % mod;
    }
    tmp = (int64_t)tmp * tmp % mod;
    k >>= 1;
  }
  return res;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<vector<int>> g(n);
  vector<int> cap(n);
  vector<int> c_size = {0};
  int root;
  for (int i = 0, par; i < n; i++) {
    cin >> cap[i] >> par;
    --par;
    if (par == -1) {
      root = i;
    } else {
      g[par].push_back(i);
    }
    c_size.push_back(cap[i]);
  }
  sort(c_size.begin(), c_size.end());
  c_size.erase(unique(c_size.begin(), c_size.end()), c_size.end());
  vector<int> T_size(n);
  function<int(int)> dfs_calc = [&](int u) {
    T_size[u] = 1;
    for (auto &v : g[u]) {
      T_size[u] += dfs_calc(v);
    }
    return T_size[u];
  };
  dfs_calc(root);
  vector<vector<vector<int64_t>>> dyn(n, vector<vector<int64_t>>(sz(c_size)));
  vector<int64_t> null(n + 1, 0);
  function<vector<int64_t>(int, int)> doit = [&](int u, int range) {
    if (range == sz(c_size)) return null;
    if (sz(dyn[u][range])) return dyn[u][range];
    vector<int64_t> ret(T_size[u] + 1, 0);
    vector<int64_t> nxt = doit(u, range + 1);
    for (int i = 0; i < nxt.size(); i++) {
      ret[0] = (ret[0] + nxt[i]) % mod;
    }
    int64_t Prob = 1LL *
                   max(0, min(cap[u], c_size[range]) - c_size[range - 1]) %
                   mod * fpow(cap[u], mod - 2) % mod;
    if (Prob == 0) return dyn[u][range] = ret;
    ret[1] = Prob;
    int tree_sz = 1;
    for (auto &v : g[u]) {
      vector<int64_t> poly = doit(v, range);
      tree_sz += T_size[v];
      for (int i_sz = tree_sz; i_sz >= 1; i_sz--) {
        ret[i_sz] = 1LL * ret[i_sz] % mod * poly[0] % mod;
        for (int j_sz = 1; j_sz <= min(i_sz - 1, T_size[v]); j_sz++) {
          ret[i_sz] += 1LL * ret[i_sz - j_sz] % mod * poly[j_sz] % mod;
        }
      }
    }
    for (int i = 1; i <= T_size[u]; i++) {
      ret[i] = 1LL * ret[i] % mod * fpow(i, mod - 2) % mod;
    }
    return dyn[u][range] = ret;
  };
  int64_t ret = 0;
  auto Prob = doit(root, 1);
  for (int i = 0; i < Prob.size(); i++) {
    ret += Prob[i];
    ret %= mod;
    //  cout << Prob[i] << '\n';
  }
  cout << ret << '\n';
  return 0;
}