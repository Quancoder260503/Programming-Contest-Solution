#include "bits/stdc++.h"

using namespace std;

const int N = 5e5 + 10;
const int MOD = 998244353; 

struct Node {
  int len, link, en ; 
  map<char, int> nxt;
};

struct SuffixTree { 
 vector<Node>node;
 int sz, last;
 vector<vector<int>>g; 
 SuffixTree(int n) { 
  node.assign(n, Node()); 
  node[0].link = -1;
  node[0].len = 0;
  sz = 1;
  last = 0;
 }
 void extend(char c) {
  int cur = sz++;
  node[cur].len = node[last].len + 1;
  node[cur].en = true; 
  int p = last;
  while (p != -1 && !node[p].nxt.count(c)) {
    node[p].nxt[c] = cur;
    p = node[p].link;
  }
  if (p == -1) {
    node[cur].link = 0;
  } else {
    int at = node[p].nxt[c];
    if (node[p].len + 1 == node[at].len) {
      node[cur].link = at;
    } else {
      int ncur = sz++;
      node[ncur].len = node[p].len + 1;
      node[ncur].nxt = node[at].nxt;
      node[ncur].link = node[at].link;
      node[ncur].en = false; 
    //  cout << ncur << " " << node[ncur].en << '\n'; 
      while (p != -1 && node[p].nxt[c] == at) {
        node[p].nxt[c] = ncur;
        p = node[p].link;
      }
      node[at].link = node[cur].link = ncur;
    }
  }
  last = cur;
  return;
 }
 void createGraph() { 
  g.resize(sz); 
  for(int i = 1; i < sz; i++) { 
   g[node[i].link].push_back(i);  
  }
 }
 int dfs(int u, int p, int64_t &ans) {
  int num_Leaf = node[u].en; 
  for(auto v : g[u]) { 
    num_Leaf += dfs(v, u, ans);
  }
  if(u) { 
   ans += 1LL * num_Leaf * num_Leaf * (node[u].len - node[p].len); 
  } 
  //cout << u << " " << num_Leaf << '\n'; 
  return num_Leaf; 
 } 
}; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 for(cin >> T; T--; ) { 
  string s; 
  cin >> s;
  SuffixTree tree(s.size() * 2); 
  for(auto &c : s) { 
   tree.extend(c); 
  }
  int64_t ret = 0; 
  tree.createGraph(); 
  tree.dfs(0, -1, ret); 
  cout << ret % MOD << '\n'; 
 }
 return 0; 
}