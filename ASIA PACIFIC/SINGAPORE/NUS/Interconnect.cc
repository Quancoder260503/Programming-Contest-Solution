#include "bits/stdc++.h"
 
using namespace std;
 
struct PersistentDisjointSets {
 vector<int> sets, size;
 deque<array<int, 4>> history;
 int find(int v) {
  return sets[v] == v ? v : sets[v] = find(sets[v]);
 }
 bool unite(int u, int v) {
  int u_set = find(u), v_set = find(v);
  if (u_set != v_set) {
   if (size[u_set] < size[v_set]) swap(u_set, v_set);
   history.push_back({v_set, sets[v_set], u_set, size[v_set]});
   sets[v_set] = u_set;
   size[u_set] += size[v_set];
   return true;
  }
  return false;
 }
 int record() {
  return history.size();
 }
 void reset() { 
  iota(sets.begin(), sets.end(), 0); 
  fill(size.begin(), size.end(), 1);   
 }
 void init(int n) { 
  sets.assign(n, 0); 
  size.assign(n, 1); 
  iota(sets.begin(), sets.end(), 0);
 }

 void delete_history(int version = 0) {
  history.resize(version);
 }

 void restore(int version = 0) {
  while (record() > version) {
   sets[history.back()[0]] = history.back()[1];
   size[history.back()[2]] -= history.back()[3];
   history.pop_back();  
  }
 }
};
 
 
const int maxn = (1 << 17); 
pair<int, int>edge[maxn]; 
int n, m, q, ans[maxn << 4]; 

PersistentDisjointSets dsu; 
 
void dnc(int b, int mask, vector<array<int, 3>>&arr) { 
 if(arr.empty()) return; 
 if(b == -1) { 
  for(auto &[u, v, ind] : arr) {
   ans[ind] = mask; 
  }  
  return; 
 }   
 int nmask = mask + (1 << b) - 1; 
 int version = dsu.record(); 
 for(int cmask = nmask; cmask > 0; cmask = (cmask - 1) & nmask) { 
  dsu.unite(edge[cmask].first, edge[cmask].second);   
 }
 vector<array<int, 3>>L, R; 
 for(const auto &[u, v, ind] : arr) { 
  (dsu.find(u) == dsu.find(v) ? L : R).push_back({u, v, ind}); 
 }
 dsu.restore(version); 
 dnc(b - 1, mask, L); 
 dnc(b - 1, mask | (1 << b), R); 
 return; 
}
 
int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> n >> m;  
  for(int i = 0; i < maxn; i++) { 
   edge[i] = {1, 1}; 
  }
  for(int i = 1; i <= m; i++) { 
   cin >> edge[i].first >> edge[i].second; 
  }   
  cin >> q; 
  vector<array<int, 3>>arr(q);
  for(int i = 0; i < q; i++) { 
   cin >> arr[i][0] >> arr[i][1]; 
   arr[i][2] = i; 
  }
  dsu.init(n + 2); 
  dnc(16, 0, arr); 
  for(int i = 0; i < q; i++) { 
   cout << ans[i] << '\n'; 
  }
  return 0;
}