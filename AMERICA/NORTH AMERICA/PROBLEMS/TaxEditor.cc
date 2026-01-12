#include "bits/stdc++.h"

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())

using namespace std; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 int n, m; 
 cin >> n >> m; 
 vector<pair<int64_t, int64_t>>a(n); 
 for(int i = 0; i < n; i++) { 
  cin >> a[i].first >> a[i].second; 
 }
 sort(a.begin(), a.end(), [&](pair<int64_t, int64_t> &f1, pair<int64_t, int64_t> &f2) { 
  return f1.second < f2.second;
 }); 
 int64_t lo = 1, hi = 1e14; 
 while(lo < hi) { 
  int64_t mid = (lo + hi) / 2; 
  int64_t curr = 0, cc = n;
  priority_queue<int64_t>pq; 
  for(int i = 0; i < n; i++) { 
   if(curr + a[i].first <= 1LL * mid * a[i].second) { 
    curr += a[i].first; 
    pq.push(a[i].first); 
    cc--; 
   } else { 
    if(pq.size() && pq.top() > a[i].first) { 
     curr = curr - pq.top() + a[i].first; 
     pq.pop(); 
     pq.push(a[i].first);    
     //cc++; 
    }
   } 
  } 
  if(cc <= m) hi = mid; 
  else lo = mid + 1; 
 }
 cout << lo << '\n';
 return 0;
}