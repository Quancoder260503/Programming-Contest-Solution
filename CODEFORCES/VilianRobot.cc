#include "bits/stdc++.h"

using namespace std;

#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

struct AhoCorasick {
  enum { alpha = 26, first = 'A' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], done = 0, start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;
  void insert(string &s, int j) {
    assert(!s.empty());
    int n = 0;
    for (int i = 0; i < sz(s); i++) {
      char c = s[i]; 
      int &m = N[n].next[c - first];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].nmatches++;
    N[n].done++; 
    return; 
  }
  AhoCorasick(vector<string> &pat) : N(1, -1) {
    for (int i = 0; i < sz(pat); i++) {
      insert(pat[i], i);
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
          N[ed].done += N[y].done; 
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

const int maxc = 1002; 
const int maxf = 7000; 

int dyn[maxc][maxf];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m; 
  cin >> n >> m;
  vector<string>pat(n);
  for(int i = 0; i < n; i++) { 
    cin >> pat[i]; 
  }
  AhoCorasick aho(pat); 
  memset(dyn, -1, sizeof(dyn)); 
  dyn[0][0] = 0; 
  for(int i = 0; i < m; i++) { 
    for(int j = 0; j < sz(aho.N); j++) { 
      if(dyn[i][j] == -1) continue; 
      for(auto c : {'A', 'B', 'C'}) {
        int nxt_node = aho.N[j].next[c - aho.first];
        dyn[i + 1][nxt_node] = max(dyn[i + 1][nxt_node], dyn[i][j] + aho.N[nxt_node].done); 
      }
    }
  }
  int ret = 0; 
  for(int i = 0; i < sz(aho.N); i++) { 
    ret = max(ret, dyn[m][i]); 
  }
  cout << ret << '\n'; 
  return 0;
}
/*

*/