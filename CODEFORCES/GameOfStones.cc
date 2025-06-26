#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
 map<pair<int, int64_t>, int>g;
 function<int(int, int64_t, int)> grundy = [&](int stones, int64_t mask, int numMoves) {
  if(stones == 0) return 0; 
  for(int i = stones; i < numMoves; i++) { 
   if(mask & (1LL << i)) { 
    mask = mask ^ (1LL << i); 
   } 
  } 
  if(g.count({stones, mask})) return g[{stones, mask}]; 
  int ret = 0; 
  set<int>s; 
  for(int i = 0; i < numMoves; i++) { 
   if(mask & (1LL << i)) { 
    s.insert(grundy(stones - i - 1, mask ^ (1LL << i), stones)); 
   } 
  } 
  int mex = 0; 
  while(s.count(mex)) mex++; 
  return g[{stones, mask}] = mex; 
 };
 vector<int>gr(70); 
 for(int i = 0; i < sz(gr); i++) { 
  gr[i] = grundy(i, (1LL << i) - 1, 61); 
 } 
 int N;
 cin >> N; 
 int ret = 0; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  ret = ret ^ gr[x]; 
 } 
 cout << (ret ? "NO" : "YES") << '\n'; 
 return 0; 
}