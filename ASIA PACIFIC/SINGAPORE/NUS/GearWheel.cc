#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define ll long long
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()


struct Dinic {
 struct Edge {
  int to, rev;
  ll c, oc;
  ll flow() { return max(oc - c, 0LL); }
 };
 vector<int>lvl, ptr, q;
 vector<vector<Edge>>adj;
 Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
 void addEdge(int a, int b, ll c, ll rcap = 0) {
 // cout << a << " " << b << " " << c << '\n';
  adj[a].push_back({b, sz(adj[b]), c, c});
  adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
 }
 ll dfs(int v, int t, ll f) {
  if(v == t || !f) return f;
  //cout << v << " " << t << " " << f << '\n';
  for(int &i = ptr[v]; i < sz(adj[v]); i++) {
   Edge &e = adj[v][i];
   if(lvl[e.to] == lvl[v] + 1) {
    if(ll p = dfs(e.to, t, min(f, e.c))) {
     e.c -= p;
     adj[e.to][e.rev].c += p;
     return p;
    }
   }
  }
  return 0;
 }
 ll maxFlow(int s, int t) {
  ll flow = 0; q[0] = s;
  for(int L = 0; L < 31; L++) do {
   lvl = ptr = vector<int>(sz(q));
   int qi = 0, qe = lvl[s] = 1;
   while(qi < qe && !lvl[t]) {
    int v = q[qi++];
    for(Edge e : adj[v]) {
     if(!lvl[e.to] && e.c >> (30 - L)) {
      q[qe++] = e.to;
      lvl[e.to] = lvl[v] + 1;
     }
    }
   }
   while(ll p = dfs(s, t, LLONG_MAX)) flow += p;
  } while(lvl[t]);
  return flow;
 }
 void rec(int n, vector<vector<int>>&ret, int s, int t, vector<int>&curr) {
  if(s == t) {
   ret.push_back(curr);
   return;
  }
  for(Edge e : adj[s]) {
   if(e.c == 0) {
    if(s == 2 * n && e.to >= n)     continue;
    if(s < n      && e.to != n + s) continue;
    curr.push_back(e.to);
    rec(n, ret, e.to, t, curr);
    curr.pop_back();
   }
  }
  return;
 }
};


int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int n;
 cin >> n;
 vector<ll>a(n);
 for(int i = 0; i < n; i++) {
  cin >> a[i];
 }
 vector<int>dp(n, 1);
 vector<vector<int>>par(n);
 for(int i = 0; i < n; i++) {
  for(int  j = 0; j < i; j++) if(a[i] % a[j] == 0 || a[j] % a[i] == 0) {
   if(dp[i] < dp[j] + 1) {
    par[i].clear();
    dp[i] = dp[j] + 1;
    par[i].push_back(j);
   } else if(dp[i] == dp[j] + 1) {
    par[i].push_back(j);
   }
  }
 }
 int max_dp = *max_element(dp.begin(), dp.end());
 cout << max_dp << ' ';
 Dinic dinic(2 * n + 2);
 int src = 2 * n, sink = src + 1;
 for(int i = 0; i < n; i++) {
  dinic.addEdge(i, n + i, 1);
  if(dp[i] == 1) {
   dinic.addEdge(src, i, 1);
  } else if(dp[i] == max_dp) {
   dinic.addEdge(n + i, sink, 1);
  }
  for(auto &x : par[i]) {
   dinic.addEdge(n + x, i, 1);
  }
 }
 cout << dinic.maxFlow(src, sink) << '\n';
 vector<vector<int>>ret;
 vector<int>curr;
 dinic.rec(n, ret, src, sink, curr);
 //cout << sz(ret) << '\n';
 for(auto &x : ret) {
  int cnt = 0;
  for(int j = 0; j < sz(x); j += 2) {
   cout << x[j] + 1 << ' ';
   cnt++;
   if(cnt == max_dp) break;
  }
  cout << '\n';
 }
 return 0;
}
