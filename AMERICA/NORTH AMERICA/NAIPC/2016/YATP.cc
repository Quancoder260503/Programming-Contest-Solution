#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int64_t oo = LLONG_MAX / 1000; 
const int C = 1e6 + 10; 

struct Line {
  int64_t m, b;
  int64_t operator()(int64_t x) { return 1LL * m * x + b; }
};
struct Node {
  Line seg;
  Node *lson, *rson;
  Node(Line _seg): seg(_seg), lson(0), rson(0) {} 
};
void insert(int l, int r, Line seg, Node* o) {
  if(l + 1 == r) {
    if(seg(l) < o->seg(l)) o->seg = seg;
    return;
  }
  int mid = (l + r) >> 1;
  if(seg.m < o->seg.m) swap(seg, o->seg);
  if(o->seg(mid) > seg(mid)) {
    swap(seg, o->seg);
    if(o->rson) insert(mid, r, seg, o->rson);
    else o->rson = new Node(seg);
  }
  else {
    if(o->lson) insert(l, mid, seg, o->lson);
    else o->lson = new Node(seg);
  }
}
int64_t query(int l, int r, int x, Node* o) {
  if(l + 1 == r) return o->seg(x);
  int mid = (l + r) >> 1;
  if(x < mid && o->lson) return min(o->seg(x), query(l, mid, x, o->lson));
  else if(o->rson) return min(o->seg(x), query(mid, r, x, o->rson));
  return o->seg(x);
}

vector<vector<pair<int, int>>> g;
vector<int>tree_sz, vis; 
vector<int64_t>w, dyn; 
int N;

int dfs(int u, int p) { 
  tree_sz[u] = 1; 
  for(auto [v, _] : g[u]) { 
    if(v == p || vis[v]) continue; 
    tree_sz[u] += dfs(v, u); 
  }
  return tree_sz[u]; 
}

int get_centroid(int u, int p, int sz) { 
  for(auto [v, _] : g[u]) if(!vis[v] && v != p && tree_sz[v] > sz / 2) { 
    return get_centroid(v, u, sz); 
  }
  return u; 
}

void get_path(int u, int p, int64_t cost, Node *root, int op) { 
  if(op) { insert(-C, C, {w[u], cost}, root); } 
  else   { dyn[u] = min(dyn[u], cost + query(-C, C, w[u], root)) ; }
  for(auto [v, cc] : g[u]) if(!vis[v] && v != p) { 
    get_path(v, u, cost + cc, root, op); 
  }
  return; 
}

void doit(int u, int p) { 
  int cc = dfs(u, p); 
  int centroid = get_centroid(u, p, cc); 
  vis[centroid] = true; 
  Node *root = new Node({w[centroid], 0}); 
  for(auto [v, cost] : g[centroid]) if(!vis[v]) { 
    get_path(v, centroid, cost, root, 0); 
    get_path(v, centroid, cost, root, 1); 
  }
  dyn[centroid] = min(dyn[centroid], query(-C, C, w[centroid], root)); 
  for(auto [v, _] : g[centroid]) if(!vis[v]) { 
    doit(v, centroid);
  }
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  g.resize(N);
  w.resize(N);
  vis.resize(N); 
  tree_sz.resize(N); 
  dyn.resize(N); 
  for(int i = 0; i < N; i++) { 
    cin >> w[i]; 
    dyn[i] = 1LL * w[i] * w[i];
  } 
  for(int i = 0, u, v, w; i < N - 1; i++) { 
    cin >> u >> v >> w; 
    --u, --v; 
    g[u].push_back({v, w}); 
    g[v].push_back({u, w}); 
  }
  doit(0, -1); 
  fill(vis.begin(), vis.end(), false); 
  for(int i = 0; i < N; i++) { 
    reverse(g[i].begin(), g[i].end()); 
  }
  doit(0, -1); 
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) { 
   // cout << dyn[i] << '\n'; 
    ret += dyn[i]; 
  }
  cout << ret << '\n'; 
  return 0;
}