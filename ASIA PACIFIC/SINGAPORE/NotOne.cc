#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())


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

const int maxn = 1e6 + 2; 

vector<pair<int, int>>pos[maxn]; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n; 
 cin >> n; 
 set<int>primes; 
 vector<int>a(n);
 int ones = 0;  
 for(int i = 0; i < n; i++) { 
  cin >> a[i]; 
  ones += (a[i] > 1); 
 }
 for(int i = 0, u, v; i < n - 1; i++) { 
  cin >> u >> v; 
  --u, --v; 
  int g = gcd(a[u], a[v]); 
  for(int j = 2; j * j <= g; j++) { 
   if(g % j == 0) { 
    primes.insert(j); 
    pos[j].push_back({u, v}); 
    // cout << u << " " << v << '\n'; 
    while(g % j == 0) g = g / j; 
   }
  }
  if(g > 1) { 
    primes.insert(g); 
    pos[g].push_back({u, v}); 
  }
 }
 PersistentDisjointSets dsu;
 dsu.init(n); 
 int ret = ones > 0; 
 for(auto p : primes) { 
  for(auto [u, v] : pos[p]) { 
   dsu.unite(u, v); 
  }
  for(auto [u, v] : pos[p]) { 
   ret = max({ret, dsu.size[u], dsu.size[v]}); 
   dsu.size[u] = dsu.size[v] = 1;  
   dsu.sets[v] = v;
   dsu.sets[u] = u;  
  }
 }
 cout << ret << '\n'; 
 return 0; 
}