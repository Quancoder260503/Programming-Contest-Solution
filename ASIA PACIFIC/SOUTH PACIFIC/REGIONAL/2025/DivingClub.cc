#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define ll long long 


int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, m, l, r;
 cin >> n >> m >> l >> r; 
 vector<int>a(n), b(n), c(m), d(m); 
 for(int i = 0; i < n; i++) { 
  cin >> a[i] >> b[i]; 
 } 
 for(int i = 0; i < m; i++) { 
  cin >> c[i] >> d[i]; 
 }
 using T = pair<int, int>; 
 priority_queue<T, vector<T>, greater<T>>pq;
 ll ans = 0;  
 for(int i = 0, ptr = 0; i < m; i++) { 
  while(ptr < n && a[ptr] + l <= c[i]) { 
   pq.push({a[ptr], b[ptr]});
   ptr++;  
  }
  while(pq.size() && d[i] > 0) { 
   auto [day, amt] = pq.top();
   pq.pop();  
   if(day + r < c[i]) continue; 
   int cc = min(d[i], amt); 
   d[i] = d[i] - cc; 
   amt  = amt  - cc; 
   ans += cc; 
   if(amt > 0) { 
    pq.push({day, amt}); 
   }
  }
 }
 cout << ans << '\n'; 
 return 0;
}
