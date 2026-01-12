#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())
#define int64_t long long

using type = int64_t; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, m; 
 cin >> n >> m; 
 vector<int>a(n); 
 for(auto &x : a) { 
  cin >> x; 
 }
 sort(a.rbegin(), a.rend());
 int mx = a[0]; 
 auto check = [&](int x) { 
  if(mx > x) return false; 
  int cm = 0; 
  vector<int>vis(n);
  using T = pair<int, int>; 
  priority_queue<T, vector<T>, greater<T>>pq; 
  for(int i = 0; i < n; i++) { 
   pq.push({a[i], i}); 
  } 
  for(int i = 0; i < n; i++) { 
   if(vis[i]) continue;
   vis[i] = 1; 
   int sum = a[i]; 
   while(pq.size() && !vis[pq.top().second] && sum + pq.top().first <= x) {
    sum += pq.top().first; 
    vis[pq.top().second] = 1; 
    pq.pop();  
   }
   cm++; 
  }
  return cm <= m; 
 }; 
 int lo = 0, hi = 1e9; 
 while(lo < hi) { 
  int mid = (lo + hi) / 2; 
  if(check(mid)) { 
   hi = mid; 
  } else { 
   lo = mid + 1; 
  }
 }
 cout << lo << '\n';
 return 0; 
}