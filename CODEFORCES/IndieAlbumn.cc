#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

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

struct AhoCorasick {
  enum { alpha = 26, first = 'a' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha];
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  AhoCorasick(vector<array<int, 3>> &pat, vector<pair<int, string>> &query) : N(1, -1) {
    vector<vector<int>>graph(sz(pat) + 1); 
    vector<int>pos(sz(pat)); 
    vector<vector<pair<int, int>>>qs(sz(pat)); 
    for(int i = 0; i < sz(query); i++) { 
      int ind = query[i].first; 
      string s = query[i].second; 
      int st = 0; 
      for(auto &c : s) { 
        int &m = N[st].next[c - first]; 
        if(m == -1) { 
          m = st = sz(N); 
          N.emplace_back(-1); 
        }
        else { 
          st = m; 
        }
      }
      qs[ind].push_back({st, i}); 
    }
    for (int i = 0; i < sz(pat); i++) {
      int type = pat[i][0]; 
      if(type == 1) { 
        if(N[0].next[pat[i][1]] == -1) {
          N[0].next[pat[i][1]] = sz(N);  
          N.emplace_back(-1);  
        }
        pos[i] = N[0].next[pat[i][1]]; 
        graph[sz(pat)].push_back(i); 
      }
      else { 
        int prevPos = pos[pat[i][1]]; 
        int nextChar = pat[i][2]; 
        if(N[prevPos].next[nextChar] == -1) { 
          N[prevPos].next[nextChar] = sz(N); 
          N.emplace_back(-1); 
        }
        pos[i] = N[prevPos].next[nextChar];
        graph[pat[i][1]].push_back(i);
        //cout << i << " " << pat[i][1] << '\n'; 
      }
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
          q.push(ed);
        }
      }
    }
    vector<vector<int>>g(sz(N)); 
    for(int i = 1; i < sz(N) - 1; i++) { 
      g[N[i].back].push_back(i);
    } 
    FT fenw(sz(N) + 7); 
    vector<int>in(sz(N) + 1), out(sz(N) + 1); 
    int timer = 0; 
    function<void(int)> dfs = [&](int u) { 
      in[u] = timer++; 
      for(auto v : g[u]) { 
        dfs(v); 
      }
      out[u] = timer - 1; 
    }; 
    dfs(0); 
    vector<int>ret(sz(query)); 
    function<void(int)> dfs2 = [&](int u) { 
      fenw.update(in[pos[u]], 1);
    //  cout << u << " " << pos[u] << '\n'; 
      for(auto v : graph[u]) { 
        dfs2(v); 
      }
      for(auto [ind, num] : qs[u]) { 
       // cout << ind  << " " << in[ind] << " " << '\n';  // fenw.query(out[ind]) << " " << fenw.query(in[pos[u]] - 1) << '\n'; 
        ret[num] = fenw.query(out[ind]) - fenw.query(in[ind] - 1); 
      }
      fenw.update(in[pos[u]], -1); 
    }; 
    for(int i = 0; i < sz(pat); i++) { 
      if(pat[i][2] == -1) {
        dfs2(i); 
      }
    }
    for(int i = 0; i < sz(query); i++) { 
      cout << ret[i] << '\n'; 
    } 
  }
};

int main(void) {
  ios_base::sync_with_stdio(true); 
  cin.tie(0); 
  cout.tie(0); 
  int N, Q; 
  cin >> N; 
  vector<array<int, 3>>pat; 
  for(int i = 0; i < N; i++) { 
    int T, pos;
    char c;  
    cin >> T; 
    if(T == 1) { 
      cin >> c; 
      pat.push_back({T, c - 'a', -1});  
    }
    else { 
      cin >> pos >> c; 
      pat.push_back({T, pos - 1, c - 'a'}); 
    }
  }
  cin >> Q; 
  vector<pair<int, string>>query; 
  for(int iter = 0; iter < Q; iter++) { 
    string s; int pos; 
    cin >> pos >> s; 
    query.push_back({pos - 1, s}); 
  }
  AhoCorasick aho(pat, query); 
  return 0; 
}