#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

template <int D, typename T>
struct Vec : public vector<Vec<D - 1, T>> {
  static_assert(D >= 1, "Dimension must be positive");
  template <typename... Args>
  Vec(int n = 0, Args... args)
      : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};
template <typename T>
struct Vec<1, T> : public vector<T> {
  Vec(int n = 0, T val = T()) : vector<T>(n, val) {}
};

const int mod = 1e9 + 7;

const int maxf = 2e6 + 10;

int64_t fact[maxf], ifact[maxf], fib[maxf];

vector<int> prefix_function(const string &s) {
  int n = sz(s);
  vector<int> pi(n + 1);
  for (int i = 2; i <= n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i - 1] != s[j]) j = pi[j];
    if (s[i - 1] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

int get_next(vector<int> &pi, string &s, int pos, char c) {
  if (pos == sz(s)) pos = pi[pos];
  while (pos > 0 && c != s[pos]) pos = pi[pos];
  if (s[pos] == c) pos++;
  return pos;
}

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init(); 
  int T, N, M;
  string S;
  vector<string> g; 
  for (cin >> T; T--;) {
    cin >> N >> M >> S;
    assert(sz(S) > 0);
    assert(N > 0);
    assert(M > 0); 
    g.resize(N); 
    for (int i = 0; i < N; i++) {
      cin >> g[i];
    }
    if(sz(S) > N + M) { 
      cout << 0 << '\n'; 
      continue; 
    }
    vector<int> kmp = prefix_function(S);
    Vec<3, int64_t> ways(N, M, sz(kmp) + 1, -1); 
    function<int64_t(int, int, int)> memo = [&](int ni, int nj, int state) -> int64_t { 
      if(ni >= N || nj >= M) return 0;
      if(state == sz(kmp) - 1) return Comb((N - ni - 1) + (M - nj - 1), (N - ni - 1)); 
      int64_t &ret = ways[ni][nj][state];
      if(ret != -1) return ret; 
      ret = 0; 
      if(ni + 1 < N) { 
        int nextState = get_next(kmp, S, state, g[ni + 1][nj]); 
        (ret += memo(ni + 1, nj, nextState)) %= mod; 
      }   
      if(nj + 1 < M) { 
        int nextState = get_next(kmp, S, state, g[ni][nj + 1]); 
        (ret += memo(ni, nj + 1, nextState)) %= mod; 
      }
      return ret; 
    }; 
    cout << memo(0, 0, get_next(kmp, S, 0, g[0][0])) << '\n'; 
  }
  return 0;
}