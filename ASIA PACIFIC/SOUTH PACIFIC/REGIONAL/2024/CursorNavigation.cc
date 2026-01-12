#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define ll long long

const int maxn = 4e5 + 10;
const int MOD = 1e9 + 7;
const int oo = 1e9;

int depth[maxn], match[maxn], node[maxn], up[maxn][20];
ll dp_out[maxn][20][2][2];
unordered_map<int, ll> dp_in[maxn];
vector<ll> prefix[maxn], suffix[maxn];
vector<int> g[maxn], adj[maxn];
pair<int, int> range[maxn];
stack<int> stk;
string S;
int n, st, en;

ll mod_pow(ll a, ll b, ll p) {
  ll res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

ll mod_inv(ll a, ll p) { return mod_pow(a % p, p - 2, p); }

void build_tree(int L, int R, int id, int &cnt) {
  if (L + 1 == R) {
    assert(match[L] == R);
    range[id] = make_pair(L, R);
    node[L] = node[R] = id;
    dp_in[L][R] = 2; 
    return;
  }
  if (R == match[L]) {
    int child = ++cnt;
    g[id].push_back(child);
    range[id] = make_pair(L, R);
    build_tree(L + 1, R - 1, child, cnt);
    node[L] = node[R] = id;
    dp_in[L][R] = 1 + dp_in[L + 1][R - 1] % MOD;
    // cerr << id << " " << child << '\n';
  } else {
    int64_t ans = 1;
    for (int current = L; current < R; current = match[current] + 1) {
      int next_child = ++cnt;
      g[id].push_back(next_child);
      build_tree(current, match[current], next_child, cnt);
      prefix[id].push_back(dp_in[current][match[current]]);
    }
    suffix[id] = prefix[id];
    for (int i = 1; i < sz(prefix[id]); i++) {
      prefix[id][i] = prefix[id][i] * prefix[id][i - 1] % MOD;
    }
    for (int i = sz(suffix[id]) - 2; i >= 0; i--) {
      suffix[id][i] = suffix[id][i] * suffix[id][i + 1] % MOD;
    }
    range[id] = make_pair(L, R);
    dp_in[L][R] = prefix[id].back();
  }
  return;
}

void dfs(int u) {
  int par = up[u][0];
  if (par != -1) {
    if (range[u].first == range[par].first + 1 && range[u].second + 1 == range[par].second) {
      dp_out[u][0][0][0] = dp_out[u][0][1][1] = 1;
      if (match[range[u].first] == range[u].second) {
        dp_out[u][0][0][1] = dp_out[u][0][1][0] = 1;
      }
    } else {
      int pos = lower_bound(g[par].begin(), g[par].end(), u) - g[par].begin();
      dp_out[u][0][0][0] = (pos ? prefix[par][pos - 1] : 1);
      dp_out[u][0][0][1] = (pos + 1 < sz(suffix[par]) ? suffix[par][pos + 1] : 1);
      dp_out[u][0][1][0] = (pos ? prefix[par][pos - 1] : 1);
      dp_out[u][0][1][1] = (pos + 1 < sz(suffix[par]) ? suffix[par][pos + 1] : 1);
    }
  }
  for (int i = 1; i < 20; i++) {
    up[u][i] = up[up[u][i - 1]][i - 1];
    for (int a = 0; a < 2; a++) {
      for (int b = 0; b < 2; b++) {
        for (int c = 0; c < 2; c++) {
          dp_out[u][i][a][b] += dp_out[u][i - 1][a][c] * dp_out[up[u][i - 1]][i - 1][c][b] % MOD;
          dp_out[u][i][a][b] %= MOD;
        }
      }
    }
  }
  for (auto v : g[u]) {
    up[v][0] = u;
    depth[v] = depth[u] + 1;
    dfs(v);
  }
  return;
}

int LCA(int u, int v) {
  if (depth[u] < depth[v]) swap(u, v);
  int d = depth[u] - depth[v];
  for (int i = 0; i < 20; i++) {
    if (d & (1 << i)) {
      u = up[u][i];
    }
  }
  if (u == v) return u;
  for (int i = 19; i >= 0; i--) {
    int tu = up[u][i], tv = up[v][i];
    if (tu != tv) u = tu, v = tv;
  }
  return up[u][0];
}

int get_anc(int u, int d) {
  for (int bit = 0; bit < 20; bit++) {
    if (d >> bit & 1) {
      u = up[u][bit];
    }
  }
  return u;
}

ostream &operator<<(ostream &out, const array<array<ll, 2>, 2> &mat) {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      out << mat[i][j] << ' ';
    }
    out << '\n';
  }
  return out;
}

array<array<ll, 2>, 2> get_ways(int u, int d) {
  array<array<ll, 2>, 2> mat;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      mat[i][j] = 0;
    }
  }
  mat[0][0] = mat[1][1] = 1;
  for (int bit = 0; bit < 20; bit++) {
    if (d >> bit & 1) {
      array<array<ll, 2>, 2> new_mat;
      for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
          new_mat[a][b] = 0;
          for (int c = 0; c < 2; c++) {
            new_mat[a][b] += mat[a][c] * dp_out[u][bit][c][b] % MOD;
            new_mat[a][b] %= MOD;
          }
        }
      }
      mat = new_mat;
      u = up[u][bit];
      // cout << mat << '\n';
    }
  }
  return mat;
}

array<ll, 2> get_ways_combine(int u, int side_u, int d) {
  int par = up[u][0];
  array<array<ll, 2>, 2> ways_to_anc = get_ways(par, d);
  array<ll, 2> ways_to_par;
  array<ll, 2> ways; 
  if (range[par].first + 1 == range[u].first && range[u].second + 1 == range[par].second) {
    ways_to_par[0] = (side_u ? dp_in[range[u].first][range[u].second] : 1);
    ways_to_par[1] = (side_u ? 1 : dp_in[range[u].first][range[u].second]);
  } else {
    int pos = lower_bound(g[par].begin(), g[par].end(), u) - g[par].begin();
    ways_to_par[0] = (side_u ? prefix[par][pos] : (pos ? prefix[par][pos - 1] : 1));
    ways_to_par[1] = (side_u ? (pos + 1 < sz(suffix[par]) ? suffix[par][pos + 1] : 1) : suffix[par][pos]);
  }
  ways[0] = (ways_to_par[0] * ways_to_anc[0][0] % MOD + ways_to_par[1] * ways_to_anc[1][0] % MOD) % MOD;
  ways[1] = (ways_to_par[0] * ways_to_anc[0][1] % MOD + ways_to_par[1] * ways_to_anc[1][1] % MOD) % MOD;
  return ways;
}

vector<string> generateParenthesis(int n) {
  vector<string> ret;
  n = n * 2;
  for (int i = 0; i < (1 << n); i++) {
    string curr = "";
    for (int j = 0; j < n; j++) {
      curr += (i & (1 << j) ? '(' : ')');
    }
    int open = 0, close = 0, flag = true;
    for (int j = 0; j < n; j++) {
      if (open < close) {
        flag = false;
        break;
      }
      open += (curr[j] == '(');
      close += (curr[j] == ')');
    }
    flag &= (open == close);
    if (flag) ret.push_back(curr);
  }
  return ret;
}

ll brute_force() {
  vector<vector<ll>> dp(n, vector<ll>(1 << n));
  dp[st][1 << st] = 1; 
  ll ans = 0;
  if(st == en) { 
   (ans += 1) %= MOD; 
  }
  for (int mask = 0; mask < (1 << n); mask++) {
    for (int i = 0; i < n; i++) {
      for (auto v : adj[i]) {
        if (mask & (1 << v)) continue;
        dp[v][mask | (1 << v)] += dp[i][mask];
        dp[v][mask | (1 << v)] %= MOD;
        if (v == en) {
          (ans += dp[i][mask]) %= MOD;
          // cout << i << " " << mask << " " << dp[v][mask | (1 << v)] << '\n';
        }
      }
    }
  }
  cout << ans << '\n'; 
  return ans; 
}

ll solve() {
  cin >> n >> st >> en >> S;
  for (int i = 1; i < n; i++) {
    adj[i].push_back(i - 1);
    adj[i - 1].push_back(i);
  }
  memset(up, -1, sizeof up);
  for (int i = 0; i < n; i++) {
    if (S[i] == '(') {
      stk.push(i);
    } else if (S[i] == ')') {
      match[stk.top()] = i;
      match[i] = stk.top();
      stk.pop();
      adj[i].push_back(match[i]);
      adj[match[i]].push_back(i);
    }
  }
  int cnt = 0;
  build_tree(0, n - 1, 0, cnt);
  dfs(0);

  --st, --en;
  if (st == en) {
    cout << 1 << '\n';
    return 1;
  }

  //brute_force();

  int u = node[st], v = node[en];
  if (depth[u] < depth[v]) {
    swap(u, v);
    swap(st, en);
  }
  int anc = LCA(u, v);
  if (u == v) {
    int curr_node = u;
    ll ans = 0, left = 1, right = 1;
    while (curr_node != -1) {
      if (match[range[curr_node].first] == range[curr_node].second) {
        ans += left * right % MOD;
        ans %= MOD;
      }
      left = left * dp_out[curr_node][0][0][0] % MOD;
      right = right * dp_out[curr_node][0][1][1] % MOD;
      curr_node = up[curr_node][0];
    }
    (ans += dp_in[min(st, en)][max(st, en)] - 1) %= MOD;
    cout << ans << '\n';
    return ans; 

  } else if (v == anc) {
    int side_u = (range[u].first == st ? 0 : 1);
    int side_v = (range[v].first == en ? 0 : 1);
    int d = depth[u] - depth[v];
    array<ll, 2> ways = get_ways_combine(u, side_u, d - 1);
    ll ans = 0, left = 1, right = 1;
    ans += ways[side_v];
    ans %= MOD;
    int curr_node = v; 
    while (curr_node != -1) {
      if (match[range[curr_node].first] == range[curr_node].second) {
        ans += left % MOD * right % MOD * ways[1 - side_v] % MOD;
        ans %= MOD;
      }
      left = left * dp_out[curr_node][0][0][0] % MOD;
      right = right * dp_out[curr_node][0][1][1] % MOD;
      curr_node = up[curr_node][0];
    }
    cout << ans << '\n';
    return ans; 

  } else {
    int side_u = (range[u].first == st ? 0 : 1);
    int side_v = (range[v].first == en ? 0 : 1);
    int anc_u = get_anc(u, depth[u] - depth[anc] - 1);
    int anc_v = get_anc(v, depth[v] - depth[anc] - 1);
    int pos_u = lower_bound(g[anc].begin(), g[anc].end(), anc_u) - g[anc].begin();
    int pos_v = lower_bound(g[anc].begin(), g[anc].end(), anc_v) - g[anc].begin();
    if (pos_u > pos_v) {
      swap(u, v);
      swap(side_u, side_v);
      swap(anc_u, anc_v);
      swap(pos_u, pos_v);
    }
    int d_u = depth[u] - depth[anc_u];
    int d_v = depth[v] - depth[anc_v];
    array<ll, 2> ways_u, ways_v;
    if (d_u == 0) {
      ways_u[side_u] = 1;
      ways_u[1 - side_u] = dp_in[range[u].first][range[u].second];
    } else {
      array<ll, 2> ways_to_anc = get_ways_combine(u, side_u, d_u - 1);
      ways_u[0] = ways_u[1] = (ways_to_anc[0] + ways_to_anc[1]) % MOD;
    }
    if (d_v == 0) {
      ways_v[side_v] = 1;
      ways_v[1 - side_v] = dp_in[range[v].first][range[v].second];
    } else {
      array<ll, 2> ways_to_anc = get_ways_combine(v, side_v, d_v - 1);
      ways_v[0] = ways_v[1] = (ways_to_anc[0] + ways_to_anc[1]) % MOD;
    }
    ll ans = 0, left = 0, right = 0;
    left += ways_u[0] * (pos_u ? prefix[anc][pos_u - 1] : 1) % MOD;
    left %= MOD;
    right += ways_v[1] * (pos_v + 1 < sz(suffix[anc]) ? suffix[anc][pos_v + 1] : 1) % MOD;
    right %= MOD;
    int curr_node = up[anc][0];
 
    while (curr_node != -1) {
      if (match[range[curr_node].first] == range[curr_node].second) {
        ans += left * right % MOD;
        ans %= MOD;
      }
      left = left * dp_out[curr_node][0][0][0] % MOD;
      right = right * dp_out[curr_node][0][1][1] % MOD;
      curr_node = up[curr_node][0];
    }
    ll amt = 1;
    if (pos_u + 1 < pos_v) {
      amt = prefix[anc][pos_v - 1] % MOD * mod_inv(prefix[anc][pos_u], MOD) % MOD;
    }
    //cout << ways_u[1] << " " << ways_v[0] << " " << side_v << '\n'; 
    ans += ways_u[1] % MOD * ways_v[0] % MOD * amt % MOD;
    ans %= MOD;
    cout << ans << '\n'; 
    return ans; 
  }
  return 0; 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  for (T = 1; T--;) {
    solve(); 
  }
  return 0;
}