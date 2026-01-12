#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

using type = int64_t;
const int MOD = 998244353;

int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

struct AhoCorasick {
  struct Node {
    // (nmatches is optional)
    int back, next[2], start = -1, end = -1, ind = -1;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;
  void insert(string &s, int j) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int &m = N[n].next[c == 'T'];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else
        n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    if (N[n].ind == -1) {
      N[n].ind = j;
    }
    return;
  }
  AhoCorasick(vector<string> &pat) : N(1, -1) {
    for (int i = 0; i < sz(pat); i++) {
      insert(pat[i], i);
    }
    N[0].back = sz(N);
    N.emplace_back(0);
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      for (int i = 0; i < 2; i++) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1) {
          ed = y;
        } else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
          q.push(ed);
        }
      }
    }
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<string> s(n);
  for (auto &x : s) {
    cin >> x;
  }
  AhoCorasick aho(s);
  vector<vector<int64_t>> curr(sz(aho.N), vector<int64_t>(n));
  vector<vector<int64_t>> mat(n, vector<int64_t>(n));
  vector<int> vis(sz(aho.N)), cns(sz(aho.N));
  queue<int> q;
  int var = 0;
  for (q.push(0), vis[0] = cns[0] = true, curr[0][var++] = 1; q.size();
       q.pop()) {
    int u = q.front();
    if (aho.N[u].ind != -1) {
      // cout << u << " " << aho.N[u].ind << '\n';
      mat[aho.N[u].ind] = curr[u];
    } else {
      int xo = aho.N[u].next[0] ^ aho.N[u].next[1];
      for (auto c : aho.N[u].next) {
        if (!cns[c]) {
          if (!cns[c ^ xo]) {
            curr[c][var++] = 1;
          } else {
            for (int i = 0; i < n; i++) {
              curr[c][i] =
                  (2LL * curr[u][i] % MOD - curr[c ^ xo][i] + MOD) % MOD;
            }
          }
          cns[c] = true;
        }
      }
      for (auto c : aho.N[u].next) {
        if (!vis[c]) {
          vis[c] = true;
          q.push(c);
        }
      }
    }
  }
  vector<vector<int>> ind(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    ind[i][i] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (mat[j][i] != 0) {
        swap(mat[j], mat[i]);
        swap(ind[j], ind[i]);
        int64_t temp = mod_inv(mat[i][i], MOD);
        for (int k = 0; k < n; k++) {
          mat[i][k] = mat[i][k] % MOD * temp % MOD;
          ind[i][k] = ind[i][k] % MOD * temp % MOD;
        }
        for (int k = 0; k < n; k++) {
          if (i != k) {
            int64_t x = mat[k][i];
            for (int l = 0; l < n; l++) {
              (mat[k][l] += MOD - mat[i][l] % MOD * x % MOD) %= MOD;
              (ind[k][l] += MOD - ind[i][l] % MOD * x % MOD) %= MOD;
            }
          }
        }
        break;
      }
    }
  }
  for (int i = 0; i < n; i++) {
   cout << ind[0][i] << " "; 
  } 
  cout << '\n'; 
  return 0;
}