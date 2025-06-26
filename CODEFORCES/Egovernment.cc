#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
struct AhoCorasick {
  enum { alpha = 26, first = 'a' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha]; 
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  int insert(string &s, int j) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int &m = N[n].next[c - first];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else n = m;
    }
    return n; 
  }
  AhoCorasick(vector<string> &pat, vector<int>&at) : N(1, -1) {
    for (int i = 0; i < sz(pat); i++) {
      at[i] = insert(pat[i], i); 
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
vector<int>graph[1000006]; 

int main(void) {
  ios_base::sync_with_stdio(true); 
  cin.tie(0); 
  cout.tie(0);
  int N, Q; 
  cin >> Q >> N; 
  vector<string>pat; 
  string s; 
  for(int i = 0; i < N; i++) { 
    cin >> s; 
    pat.push_back(s); 
  } 
  vector<int>at(N);   
  AhoCorasick aho(pat, at); 
  for(int i = 1; i < sz(aho.N) - 1; i++) { 
    graph[aho.N[i].back].push_back(i); 
  }
  vector<int>in(sz(aho.N)), out(sz(aho.N)); 
  int timer = 0; 
  function<void(int, int)> dfs = [&](int u, int p) { 
    in[u] = timer++;
    for(auto v : graph[u]) { 
      if(v == p) continue; 
      dfs(v, u); 
    } 
    out[u] = timer - 1; 
  }; 
  dfs(0, -1); 
  FT fenw(sz(aho.N) + 7);
  for(int i = 0; i < N; i++) { 
    int p = at[i]; 
    fenw.update(in[p], 1);
    fenw.update(out[p] + 1, -1);  
  }
  vector<int>state(N, true); 
  for(int i = 0, ptr = 0; i < Q; i++) { 
    cin >> s; 
    if(s[0] == '?') { 
      int64_t ans = 0; 
      int start = 0; 
      s = s.substr(1); 
      for(auto &ch : s) { 
        start = aho.N[start].next[ch - 'a']; 
        ans += fenw.query(in[start]); 
      }
      cout << ans << '\n'; 
      ptr++; 
    }
    else {
      int c = (s[0] == '+' ? 1 : -1);
      int p = stoi(s.substr(1)) - 1;  
      if(state[p] && c == 1) { 
        continue; 
      }
      if(!state[p] && c == -1) { 
        continue; 
      }
      state[p] = state[p] ^ 1; 
      p = at[p]; 
      fenw.update(in[p], 1 * c); 
      fenw.update(out[p] + 1, -1 * c); 
    }
  } 
  return 0; 
}

/**
 *     
 * 
 */