#include <bits/stdc++.h>

using namespace std;

#define sz(x) int(x.size())
#define vi vector<int>
#define ll long long
#define rep(i, j, k) for (int i = j; i < k; i++)

const int oo = 1000000000;

struct MaxFlow {
  struct Edge {
    int to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); }  // if you need flows
  };
  vi lvl, ptr, q;
  vector<vector<Edge>> adj;
  MaxFlow(int n) : lvl(n), ptr(n), q(n), adj(n) {}
  void addEdge(int a, int b, ll c, ll rcap = 0) {
    adj[a].push_back({b, sz(adj[b]), c, c});
    adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(adj[v]); i++) {
      Edge& e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll getMaxFlow(int s, int t) {
    ll flow = 0;
    q[0] = s;
    rep(L, 0, 31) do {  // 'int L=30' maybe faster for random data
      lvl = ptr = vi(sz(q));
      int qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        int v = q[qi++];
        for (Edge e : adj[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    }
    while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, src, sink;
  cin >> N;
  src = N;
  sink = N + 1;
  MaxFlow dinic(N + 2);
  for (int i = 0, x; i < N; i++) {
    cin >> x;
    if (x == 1) {
      dinic.addEdge(src, i, oo);
    } else if (x == 2) {
      dinic.addEdge(i, sink, oo);
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0, x; j < N; j++) {
      cin >> x;
      if (x == 0) continue; 
      dinic.addEdge(i, j, x);
    }
  }
  cout << dinic.getMaxFlow(src, sink) << '\n';
  for (int i = 0; i < N; i++) {
    if (dinic.leftOfMinCut(i)) {
      cout << i + 1 << ' ';
    }
  }
  cout << '\n';
  for (int i = 0; i < N; i++) {
    if (!dinic.leftOfMinCut(i)) {
      cout << i + 1 << ' ';
    }
  }
  cout << '\n';
  return 0;
}
