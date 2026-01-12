#include "bits/stdc++.h"

using namespace std;

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int n, k; 
 cin >> n >> k;
 vector<int>a(n); 
 for(int i = 0; i < n; i++) { 
  cin >> a[i]; 
 }
 sort(a.begin(), a.end()); 
 auto check = [&](int64_t x) {
  int64_t cnt = 0; 
  for(int i = 0; i < min(n, k); i++) { 
   int64_t curr = x;  
   if(x >= a[i]) { 
    cnt += 5; 
   } else { 
    break; 
   }
   cnt += 1LL * (curr - a[i]) / (2LL * a[i]) * 4; 
   if(cnt >= n) return 1; 
  }
  return 0; 
 }; 
 int64_t lo = 0, hi = LLONG_MAX / 2; 
 while(lo < hi) { 
  int64_t mid = (lo + hi) / 2; 
  if(check(mid)) { 
    hi = mid; 
  } else { 
    lo = mid + 1; 
  }
 }
 cout << lo << '\n'; 
 return 0; 
}