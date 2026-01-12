#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

#define ll long long
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()

const ll oo = LLONG_MAX;

using vi = vector<ll>;

template<class T>
struct Dinic {
 struct Edge {
  int to, rev;
  T c, oc;
 };
 vector<int>lvl, ptr, q;
 vector<vector<Edge>>adj;
 Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
 void addEdge(int a, int b, T c, T rcap = 0) {
 // cout << a << " " << b << " " << c << '\n';
  adj[a].push_back({b, sz(adj[b]), c, c});
  adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
 }
 ll dfs(int v, int t, T f) {
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
 T maxFlow(int s, int t) {
  T flow = 0; q[0] = s;
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
   while(T p = dfs(s, t, LLONG_MAX)) flow += p;
  } while(lvl[t]);
  return flow;
 }
};

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 return 0;
}
