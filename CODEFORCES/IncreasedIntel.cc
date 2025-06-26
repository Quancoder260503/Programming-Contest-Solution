#include "bits/stdc++.h"

using namespace std;

#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

struct AhoCorasick {
  enum { alpha = 26, first = 'A' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], cost = 0, start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;
  void insert(string &s, int j, int c) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int &m = N[n].next[c - first];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else
        n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].nmatches++;
    N[n].cost += c; 
    return; 
  }
  AhoCorasick(vector<string> &pat, vector<int> &c) : N(1, -1) {
    for (int i = 0; i < sz(pat); i++) {
      insert(pat[i], i, c[i]);
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
          N[ed].cost += N[y].cost;
          q.push(ed);
        }
      }
    }
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T, N, M, K;
  for(cin >> T; T--; ) {
    cin >> N >> M >> K; 
    vector<string>pat(K); 
    vector<int>c(K); 
    vector<int>canChange(N); 
    string src;
    cin >> src; 
    for(int i = 0, x; i < M; i++) { 
      cin >> x; 
      x--; 
      canChange[x] = true; 
    }
    for(int i = 0; i < K; i++) { 
      cin >> pat[i] >> c[i]; 
    }
    AhoCorasick aho(pat, c); 
    vector<vector<int64_t>> dyn(sz(src) + 1, vector<int64_t> (sz(aho.N) + 1, -1));
    dyn[0][0] = 0; 
    for(int x = 0; x < sz(src); x++) { 
      for(int j = 0; j < sz(aho.N); j++) { 
        if(dyn[x][j] == -1) continue; 
        if(canChange[x]) { 
          for(auto c : {'A', 'T', 'G', 'C'}) { 
            int nextState = aho.N[j].next[c - 'A']; 
            dyn[x + 1][nextState] = max(dyn[x + 1][nextState], dyn[x][j] + aho.N[nextState].cost); 
          }
        }
        else { 
          int nextState = aho.N[j].next[src[x] - 'A']; 
          dyn[x + 1][nextState] = max(dyn[x + 1][nextState], dyn[x][j] + aho.N[nextState].cost); 
        }
      }
    }
    int64_t ret = 0; 
    for(int j = 0; j < sz(aho.N); j++) { 
      ret = max(ret, dyn[sz(src)][j]); 
    }
    cout << ret << '\n';     
  }
  return 0;
}
/*

*/