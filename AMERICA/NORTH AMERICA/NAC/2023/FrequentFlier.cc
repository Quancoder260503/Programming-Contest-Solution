#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, m, k; 
 cin >> n >> m >> k;
 vector<int>a; 
 for(int i = 0; i < m - 1; i++) { 
  a.push_back(0); 
 }
 for(int i = 0, x; i < n; i++) { 
  cin >> x; 
  a.push_back(x); 
 }
 for(int i = 0; i < m - 1; i++) { 
  a.push_back(0); 
 }
 vector<int>paid(sz(a)); 
 vector<pair<int, int>>stk; 
 int64_t used = 0, ret = 0; 
 for(int i = 0; i < sz(a); i++) { 
  if(i >= m) used -= paid[i - m]; 
  stk.push_back({a[i], i}); 
  while(sz(stk) && used < k) { 
   pair<int, int>curr = stk.back(); 
   stk.pop_back(); 
   if(curr.second <= i - m) continue; 
   int64_t amt = min(1LL * curr.first, k - used); 
   paid[curr.second] += amt; 
   used += amt; 
   ret += amt; 
   curr.first -= amt; 
   if(curr.first) stk.push_back({curr.first, curr.second}); 
  } 
 }
 cout << ret << '\n'; 
 return 0; 
}