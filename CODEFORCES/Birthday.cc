#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
 
const int alpha = 2;
const int first = 'a'; 
 
struct Node {
  int back, next[alpha], start = -1, end = -1; 
  Node(int v) { memset(next, v, sizeof(next)); }
};
 
vector<Node> N;
vector<int> backp;
 
const int maxf = 752; 
const int maxc = 1e7 + 1; 
 
vector<string>pat;
vector<vector<int>>g; 
vector<int> vis;
 
void insert(const char *s, int j) {
  int n = 0;
  for (int i = 0; s[i]; i++) {
    int c = s[i]; 
    int& m = N[n].next[c - first];
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
 
void AhoCorasick(int m) { 
  N.emplace_back(-1); 
  for (int i = 0; i < m; i++) {
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
  return; 
}
 
void findAll(const char *word, int target) {
  int n = 0;
  for (int i = 0; word[i]; i++) {
    int c = word[i]; 
    n = N[n].next[c - first];
    int ind = N[n].end;
    while (ind != -1) {
      if(ind != target) g[target].push_back(ind); 
      ind = backp[ind];
    }
  }
  sort(g[target].begin(), g[target].end());
  return;
}
 
bool find(int j, vector<int> &btoa) {
  if (btoa[j] == -1) return 1;
  vis[j] = 1;
  int di = btoa[j];
  for (int e : g[di])
    if (!vis[e] && find(e, btoa)) {
      btoa[e] = di;
      return 1;
    }
  return 0;
}
 
int dfsMatching(vector<int> &btoa) {
  for (int i = 0; i < sz(g); i++) {
    vis.assign(sz(btoa), 0);
    for (int j : g[i])
      if (find(j, btoa)) {
        btoa[j] = i;
        break;
      }
  }
  return sz(btoa) - (int)count(btoa.begin(), btoa.end(), -1);
}
 
void min_cover(int n) {
  vector<int> match(n, -1);
  int res = dfsMatching(match);
  vector<bool> lfound(n, true);
  fill(vis.begin(), vis.end(), 0); 
  for (int it : match)
    if (it != -1) lfound[it] = false;
  vector<int> q;
  for (int i = 0; i < n; i++)
    if (lfound[i]) q.push_back(i);
  while (!q.empty()) {
    int i = q.back();
    q.pop_back();
    lfound[i] = 1;
    for (int e : g[i])
      if (!vis[e] && match[e] != -1) {
        vis[e] = true;
        q.push_back(match[e]);
      }
  }
  res = n - res; 
  printf("%d\n", res);  
  for(int i = 0; i < n; i++) { 
    if(!lfound[i] || vis[i]) continue; 
    printf("%d ", i + 1); 
  }
  printf("\n"); 
  return; 
}
 
int main(void) {
  int n;
  scanf("%d", &n); 
  pat.resize(n); 
  vis.resize(n); 
  g.resize(n); 
  for(int i = 0; i < n; i++) { 
    cin >> pat[i]; 
  }
  AhoCorasick(n); 
  vector<vector<int>>g(n); 
  for(int i = 0; i < n; i++) { 
    findAll(pat[i].c_str(), i); 
  }
  min_cover(n); 
  return 0;
}