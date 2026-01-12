#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

struct state { 
 double prob, cost; 
 state(double _prob = 1., double _cost = 0) : prob(_prob), cost(_cost) {}; 
 void add(state other) { 
  cost += other.cost * prob;    
  prob *= other.prob;  
 }
 bool operator < (const state &other) const { 
  return -cost * (1. - other.prob) < -other.cost * (1. - prob);   
 }
};

struct Entry {  
 state s; 
 int ind, tail; 
 Entry(state _s, int _ind, int _tail) : s(_s), ind(_ind), tail(_tail) {}; 
 bool operator < (const Entry &other) const { 
  return s < other.s; 
 }
}; 


int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n;
 cin >> n; 
 vector<state>test(n); 
 vector<int>par(n), f(n + 1, -1); 
 for(int i = 0; i < n; i++) { 
  cin >> test[i].cost >> test[i].prob >> par[i]; 
  --par[i]; 
 }
 priority_queue<Entry>pq; 
 vector<int>tails(n + 1, n), nxt(n + 1, -1);
 for(int i = 0; i < n; i++) { 
  pq.push(Entry{test[i], i, tails[i] = i}); 
 } 
 function<int(int)> F = [&](int v) -> int { 
  return f[v] == -1 ? v : f[v] = F(f[v]); 
 }; 
 auto join = [&](int u, int v) { 
  u = F(u), v = F(v); 
  if(u == v) return;
  f[v] = u; 
  return; 
 }; 
 while(sz(pq)) { 
  auto [curr_state, v, tail] = pq.top(); 
  pq.pop(); 
  if(tails[v] == tail) { 
   int u = F(par[v] == -1 ? n : par[v]); 
   join(u, v); 
   nxt[tails[u]] = v; tails[u] = tail; 
  // cout << tails[u] << " " << v << '\n'; 
   if(u < n) {
    test[u].add(test[v]); 
    pq.push(Entry{test[u], u, tails[u]}); 
   }
  }
 }
 for(int i = 0, u = n; i < n; i++) { 
 cout << nxt[u] + 1 << '\n'; 
  u = nxt[u]; 
 }
 return 0; 
}