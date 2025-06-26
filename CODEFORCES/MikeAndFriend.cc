#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
struct AhoCorasick {
  enum { alpha = 26, first = 'a' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], done = false, start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;
  vector<int> insert(string &s, int j) {
    assert(!s.empty());
    int n = 0;
    vector<int>ret; 
    for (char c : s) {
      int &m = N[n].next[c - first];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else n = m;
      ret.push_back(n); 
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].nmatches++;
    N[n].done = true; 
    return ret; 
  }
  AhoCorasick(vector<string> &pat, vector<vector<int>> &occ) : N(1, -1) {
    for (int i = 0; i < sz(pat); i++) {
      occ.push_back(insert(pat[i], i));
    }
    N[0].back = sz(N);
    N.emplace_back(0);
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      for (int i = 0; i < alpha; i++) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1)
          ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
          N[ed].nmatches += N[y].nmatches;
          q.push(ed);
        }
      }
    }
  }
  vector<int> find(string word) {
    int n = 0;
    vector<int> res;  // ll count = 0;
    for (char c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);
      // count += N[n].nmatches;
    }
    return res;
  }
  vector<vector<int>> findAll(vector<string> &pat, string word) {
    vector<int> r = find(word);
    vector<vector<int>> res(sz(word));
    for (int i = 0; i < sz(word); i++) {
      int ind = r[i];
      while (ind != -1) {
        res[i - sz(pat[ind]) + 1].push_back(ind);
        ind = backp[ind];
      }
    }
    return res;
  }
};
 
struct FT {
  int N;
  vector<int> bit;
  FT(int _N) {
    N = _N;
    bit.resize(N);
  }
  int query(int i) {
    int c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c + bit[i];
    }
    return c;
  }
  void update(int i, int dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = dif + bit[i];
    }
  }
};
 
const int maxf = 5e5; 
vector<int>graph[maxf]; 
 
int main(void) {
  ios_base::sync_with_stdio(true); 
  cin.tie(0); 
  cout.tie(0); 
  int N, Q;
  cin >> N >> Q; 
  vector<string>s; 
  for(int i = 0; i < N; i++) { 
string p; cin >> p;
    s.push_back(p);
  }  
  vector<vector<int>>g; 
  AhoCorasick aho(s, g); 
  vector<array<int, 4>>query; 
  for(int iter = 0, l, r, k; iter < Q; iter++) { 
    cin >> l >> r >> k; 
    --l, --r, --k; 
    query.push_back({r, 1, iter, k}); 
    if(l > 0) query.push_back({l - 1, -1, iter, k}); 
  } 
  sort(query.begin(), query.end(), [&](array<int, 4> a, array<int, 4> b) { 
    return a[0] < b[0]; 
  }); 
  for(int i = 0; i < sz(aho.N) - 1; i++) { 
   //cout << i << " "<< aho.N[i].back << " "<< sz(graph[i])<< "\n";
   int x = aho.N[i].back; 
   graph[x].push_back(i); 
  } 
  vector<int>in(sz(aho.N)), out(sz(aho.N)); 
  int time = 0; 
  function<void(int, int)> dfs = [&](int u, int p) { 
    in[u] = time++; 
    for(auto v : graph[u]) { 
      if(v == p) continue; 
      dfs(v, u); 
    }
    out[u] = time - 1; 
  };  
  dfs(0, -1); 
  vector<int64_t> ret(Q); 
  FT fenw(time + 7); 
  for(int i = 0, ptr = 0; i < sz(query); i++) { 
    for(; ptr <= query[i][0]; ptr++) { 
      for(int j = 0; j < sz(g[ptr]); j++) { 
        fenw.update(in[g[ptr][j]] + 1, 1); 
      }
    } 
    int pos = g[query[i][3]].back(); 
    ret[query[i][2]] += query[i][1] * (fenw.query(out[pos] + 1) - fenw.query(in[pos])); 
  }
  for(int i = 0; i < Q; i++) {
    cout << ret[i] << '\n'; 
  }  
  return 0; 
}