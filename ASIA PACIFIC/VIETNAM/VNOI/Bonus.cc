#include "bits/stdc++.h"

#define sz(x) int(x.size())

using namespace std; 

const int maxn = 1e6 + 2; 

int n, m, cnt = 0, timer = 1; 
int trie[maxn][26], ind[maxn], in[maxn], out[maxn]; 
int64_t tree[maxn << 2];

vector<int>g[maxn];  

int add(const string &s) { 
 int root = 0; 
 for(int i = 0; i < sz(s); i++) { 
  if(trie[root][s[i] - 'A'] == -1) { 
   trie[root][s[i] - 'A'] = ++cnt; 
  } 
  root = trie[root][s[i] - 'A']; 
 }
 return root; 
}

void dfs(int root) { 
 in[root] = timer++; 
 for(int i = 0; i < 26; i++) { 
  if(trie[root][i] != -1) { 
    dfs(trie[root][i]); 
  }
 }
 out[root] = timer - 1; 
 return; 
}

void update(int pos, int64_t val, int tl = 1, int tr = timer, int p = 1) { 
 if(tl == tr) { 
  tree[p] = max(tree[p], val); 
  return; 
 }
 int mid = (tl + tr) / 2; 
 if(pos <= mid) update(pos, val, tl, mid, p << 1); 
 else update(pos, val, mid + 1, tr, p << 1 | 1); 
 tree[p] = max(tree[p << 1], tree[p << 1 | 1]); 
 return; 
}

int64_t query(int L, int R, int tl = 1, int tr = timer, int p = 1) { 
 if(R < tl || L > tr) return 0; 
 if(L <= tl && tr <= R) return tree[p]; 
 int mid = (tl + tr) / 2; 
 return max(query(L, R, tl, mid, p << 1), query(L, R, mid + 1, tr, p << 1 | 1)); 
}


int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  memset(trie, -1, sizeof trie); 
  // euler tour on the trie
  cin >> n >> m; 
  vector<pair<string, int>>a(n); 
  for(int i = 0; i < n; i++) { 
    cin >> a[i].first >> a[i].second; 
    ind[i] = add(a[i].first); 
  }
  dfs(0);
  for(int i = 0, u, v; i < m; i++) { 
   cin >> u >> v; 
   g[u].push_back(v); 
   g[v].push_back(u); 
  }
  vector<int64_t>dp(n); 
  unordered_map<int, int64_t>opt; 
  for(int i = 0; i < n; i++) { 
   int pos = ind[i]; 
   dp[i] = a[i].second + query(in[pos] + 1, out[pos]);
   for(auto &x : g[a[i].second]) { 
    if(opt.count(x)) { 
     dp[i] = max(dp[i], opt[x] + a[i].second); 
    } 
   }
   update(in[pos], dp[i]); 
   opt[a[i].second] = max(opt[a[i].second], dp[i]); 
  }
  cout << *max_element(dp.begin(), dp.end()) << '\n';  
  return 0; 
}

