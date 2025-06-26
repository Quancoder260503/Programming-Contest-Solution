#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

struct AhoCorasick {
  enum { alpha = 26, first = 'A' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], start = -1, end = -1;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;
  vector<int>cc;
  void insert(const char *s, int j) {
    int n = 0;
    for (int i = 0; s[i]; i++) {
      int &m = N[n].next[s[i] - first];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else
        n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    return; 
  }
  AhoCorasick(vector<string> &pat) : N(1, -1) {
    cc.resize(sz(pat)); 
    for (int i = 0; i < sz(pat); i++) { 
      cc[i] = sz(pat[i]); 
      insert(pat[i].c_str(), i);
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
          q.push(ed);
        }
      }
    }
  }
  void solve(vector<string> &pat, string &word) {
    vector<int>r; 
    int n = 0; 
    for(char &c : word) { 
      n = N[n].next[c - first];
      r.push_back(N[n].end);
    }
    n = sz(word); 
    vector<pair<int, int>> dyn(n, {-1, -1});
    for (int i = 0; i < n; i++) {
      int v = r[i];
      while (v != -1) {
        int u = i - cc[v] + 1;
        if(u > 0 && dyn[u - 1].first == -1) {
          v = backp[v]; 
          continue; 
        }
        dyn[u + cc[v] - 1] = max(dyn[u + cc[v] - 1], 
                                 {(u ? dyn[u - 1].first : 0) + sz(pat[v]) - cc[v], v});
        v = backp[v]; 
      }
    } 
    int at = n - 1;
    vector<int>ret;
    while (at >= 0) {
      int idx = dyn[at].second;
      if(idx == -1) break; 
      ret.push_back(idx); 
      at = at - cc[idx];
    }
    for(int i = sz(ret) - 1; i >= 0; i--) { 
      cout << pat[ret[i]] << " "; 
    }
    cout << '\n'; 
    return;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N;
  cin >> N;
  vector<string> pat(N), cpat(N); 
  for (int i = 0; i < N; i++) {
    cin >> pat[i]; 
    for (auto &c : pat[i]) { 
      if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') continue; 
      cpat[i] += c;
    }
  }
  AhoCorasick aho(cpat);
  string S;
  cin >> S;
  aho.solve(pat, S);
  return 0;
}