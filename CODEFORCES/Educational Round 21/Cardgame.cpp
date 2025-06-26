#include "bits/stdc++.h"
using namespace std;
#define inf 1000000000000
#define MAX 501
#define M 200005
#define mp make_pair
int n, m, k;
int DP[MAX][MAX];
vector<int> adj[MAX];
int indeg[MAX];
bool vis[M];
struct card {
  int level;
  int power;
  int magic;
};
struct Dinic {
  struct Edge {
    int to;
    long long flow, cap;
    Edge(int _to, long long _flow, long long _cap)
        : to(_to), flow(_flow), cap(_cap) {}
  };
  int N;
  vector<Edge> edges;
  vector<vector<int> > adj;
  vector<vector<int>::iterator> cur;
  void reset() {
    // cur.clear();
    edges.clear();
    for (int i = 0; i < N; i++) adj[i].clear();
  }
  void init(int _N) {
    N = _N;
    adj.resize(N);
    cur.resize(N);
  }
  vector<int> dist;
  void conn(int u, int v, long long flow) {
    adj[u].push_back(edges.size());
    edges.push_back(Edge(v, 0, flow));
    adj[v].push_back(edges.size());
    edges.push_back(Edge(u, 0, 0));
  }
  bool bfs(int s, int t) {
    dist = vector<int>(N, -1);
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    for (int i = 0; i < N; i++) cur[i] = adj[i].begin();
    while (q.size()) {
      int node = q.front();
      q.pop();
      for (int i = 0; i < adj[node].size(); i++) {
        const Edge &E = edges[adj[node][i]];
        int v = E.to;
        if (dist[v] < 0 && E.flow < E.cap) {
          dist[v] = dist[node] + 1;
          q.push(v);
        }
      }
    }
    return dist[t] + 1 > 0;
  }
  long long dfs(int s, int t, long long flow) {
    if (s == t) return flow;
    for (; cur[s] != adj[s].end(); cur[s]++) {
      Edge &E = edges[*cur[s]];
      if (dist[E.to] != dist[s] + 1 || E.flow == E.cap) continue;
      long long df = dfs(E.to, t, min(flow, E.cap - E.flow));
      if (df) {
        E.flow += df;
        edges[*cur[s] xor 1].flow -= df;
        return df;
      }
    }
    return 0;
  }
  long long maxflow(int s, int t) {
    long long ans = 0;
    while (bfs(s, t)) {
      while (long long df = dfs(s, t, inf)) {
        ans += df;
      }
    }
    return ans;
  }
};
void sieve() {
  for (int i = 2; i < M; i++) {
    if (!vis[i]) {
      for (int j = 2 * i; j < M; j += i) {
        vis[j] = 1;
      }
    }
  }
}
card cards[MAX];
Dinic Di;
bool valid(int lv) {
  Di.reset();
  // solve case if there is no 1 in the cards first;
  // if there is 1 we choose the one with the maximum power
  vector<pair<int, int> > ones;
  long long tot = 0;
  for (int i = 1; i <= n; i++) {
    if (cards[i].level > lv) continue;
    if (cards[i].magic == 1) {
      ones.push_back(mp(cards[i].power, i));
    }
  }
  sort(ones.rbegin(), ones.rend());
  int pos = -1;
  if (ones.size()) {
    pos = ones[0].second;
    Di.conn(0, pos, ones[0].first);
    tot += ones[0].first;
  }
  for (int i = 1; i <= n; i++) {
    if (cards[i].level > lv || cards[i].magic == 1) continue;
    if (cards[i].magic & 1)
      Di.conn(0, i, cards[i].power);
    else
      Di.conn(i, 2 * n + 1, cards[i].power);
    tot += cards[i].power;
  }
  for (int i = 1; i <= n; i++) {
    if (cards[i].level > lv) continue;
    if (cards[i].magic == 1 && i != pos) continue;
    if (cards[i].magic & 1) {
      for (int j = 1; j <= n; j++) {
        if (cards[j].level > lv || cards[j].magic & 1) continue;
        if (!vis[cards[i].magic + cards[j].magic]) {
          Di.conn(i, j, inf);
        }
      }
    }
  }
  long long ans = tot - Di.maxflow(0, 2 * n + 1);
  return ans >= k;
}
signed main() {
  scanf("%d%d", &n, &k);
  Di.init(2 * n + 2);
  sieve();
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", &cards[i].power, &cards[i].magic, &cards[i].level);
  }
  int r = (int)1e6 + 1;
  int l = 1;
  while (l < r) {
    int mid = (l + r) / 2;
    if (valid(mid))
      r = mid;
    else
      l = mid + 1;
  }
  printf("%d\n", l == (int)1e6 + 1 ? -1 : l);
  return 0;
}