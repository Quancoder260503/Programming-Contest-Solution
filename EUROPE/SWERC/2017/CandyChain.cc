#include "bits/stdc++.h"

using namespace std;

#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) (int)x.size()

const int oo = 1e9; 

struct AhoCorasick {
  enum { alpha = 26, first = 'a' };  // change this!
  struct Node {
    // (nmatches is optional)
    int next[alpha], cost = -oo;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  void insert(string &s, int j, int price) {
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
    N[n].cost = max(N[n].cost, price); 
    return; 
  }
  AhoCorasick(vector<string> &pat, vector<int> &cost) : N(1, -1) {
    for (int i = 0; i < sz(pat); i++) {
      insert(pat[i], i, cost[i]);
      reverse(pat[i].begin(), pat[i].end());
      insert(pat[i], i, cost[i]); 
    }
    return; 
  }
};

const int maxc = 70; 
const int maxf = 20000; 

int dyn[maxc][maxc][2][maxf];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string S;
  cin >> S; 
  int n; 
  cin >> n;
  vector<string> pattern(n); 
  vector<int> cost(n); 
  for(int i = 0; i < n; i++) { 
    cin >> pattern[i] >> cost[i]; 
  }
  AhoCorasick aho(pattern, cost);
  memset(dyn, -1, sizeof(dyn)); 
  function<int(int, int, int, int)> memo = [&](int i, int j, int full_consumption, int node) -> int { 
    if(i == j) return (full_consumption ? aho.N[node].cost : max(0, aho.N[node].cost)); 
    int &ret = dyn[i][j][full_consumption][node]; 
    if(ret != -1) return ret; 
    ret = (full_consumption ? -oo : 0); 
    int next_node = aho.N[node].next[S[i] - 'a']; 
    if(next_node != -1) { 
      ret = max(ret, memo(i + 1, j, full_consumption, next_node)); 
    }
    for(int k = i + 1; k <= j; k++) {
      //if(k == j && !node) continue; 
      int _skip = memo(i, k, node != 0, 0), _next = memo(k, j, full_consumption, node);
      if(_skip > -oo && _next > -oo) { 
        ret = max(ret, _skip + _next); 
      }
    }
    return ret;
  }; 
  cout << memo(0, sz(S), false, 0) << '\n'; 
  return 0;
}
/*

*/