#include "bits/stdc++.h"

using namespace std;

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int n, k; 
 cin >> n >> k; 
 unordered_map<int, int>mp;  
 priority_queue<pair<int, int>>pq; 
 for(int i = 0, x; i < n; i++) { 
  cin >> x; 
  mp[x]++; 
 }
 for(auto [x, y] : mp) { 
  pq.push({y, x}); 
 }
 for(int i = 0; i < k; i++) { 
  auto [_, x] = pq.top(); 
  pq.pop(); 
  mp[x]--; 
  pq.push({mp[x], x}); 
 }
 cout << pq.top().first << '\n'; 
 return 0; 
}