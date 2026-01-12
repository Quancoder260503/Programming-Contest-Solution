#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int ALPHABET = 22; 

struct AhoCorasick {
  enum { 
    alpha = ALPHABET,
    first = 'a' 
  };  
  struct Node {
    int back, next[alpha], start = -1, end = -1; 
    Node(int v) { 
     memset(next, v, sizeof(next));
    }
  };
  vector<Node> N;
  vector<int> backp;

  void insert(string &s, int j) {
    assert(!s.empty());
    int n = 0;
    for (char &c : s) {
      int &m = N[n].next[c - first];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else n = m; 
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    return; 
  }
  AhoCorasick(vector<string> &pat, vector<int64_t>&c) : N(1, -1) {
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
          q.push(ed);
        }
      }
    }
  }
  vector<int> find(string word) {
    int n = 0;
    vector<int> res;  // ll count = 0;
    for (char &c : word) {
      n = N[n].next[c - first];
      res.push_back(N[n].end);
    }
    return res;
  }
  void findAll(vector<string> &pat, string word, vector<int64_t>&occ) {
    vector<int> r = find(word);
    for (int i = 0; i < sz(word); i++) {
      int ind = r[i];
      while (ind != -1) {
        occ[ind]++;
        ind = backp[ind];
      }
    }
    return;
  }
};
 
int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n, m; 
  string S; 
  cin >> n >> m >> S;
  vector<string>pattern;
  vector<int64_t>profit; 
  unordered_map<string, int64_t>mp; 
  for(int i = 0, p; i < m; i++) { 
   string c; 
   cin >> c >> p; 
   mp[c] += p; 
  }
  for(const auto &[u, v] : mp) {
   pattern.push_back(u); 
   profit.push_back(v); 
  }
  AhoCorasick aho(pattern, profit);
  vector<int64_t>occ(sz(pattern), 0); 
  aho.findAll(pattern, S, occ); 
  vector<int64_t> dp(1 << ALPHABET);  
  for(int i = 0; i < sz(pattern); i++) { 
   int mask = 0; 
   for(auto &c : pattern[i]) { 
    mask |= (1 << (c - 'a')); 
   }    
// cerr << pattern[i] << ' ' << occ[i] << ' ' << profit[i] << '\n'; 
   dp[mask] += occ[i] * profit[i]; 
  }
  for(int i = 0; i < ALPHABET; i++) { 
   for(int mask = 0; mask < (1 << ALPHABET); mask++) { 
    if(mask >> i & 1) { 
     dp[mask] += dp[mask ^ (1 << i)]; 
    }   
   }
  }
  cout << *max_element(dp.begin(), dp.end()) << '\n'; 
  return 0; 
}