#include "bits/stdc++.h"

using namespace std;


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n, p, q, s;
  cin >> n >> p >> q >> s; 
  vector<int>a(p), b(q); 
  for(auto &x : a) { 
   cin >> x; 
  } 
  for(auto &x : b) { 
   cin >> x; 
  } 

  sort(a.begin(), a.end()); 
  sort(b.begin(), b.end()); 

  auto check = [&](int d) { 
   multiset<int>ms(b.begin(), b.end()); 
   int match = 0; 
   for(int i = p - 1; i >= 0; i--) { 
    int l = a[i] - d; 
    int r = a[i] + d;
    r = min(r, s - a[i]); 
    if(l > r) continue; 
    auto it = ms.upper_bound(r); 
    if(it != ms.begin()) { 
     --it;    
     if(*it >= l) {  
      ms.erase(it); 
      match++; 
     }
    }
   }
   return match >= n; 
  };
  int lo = 0, hi = 1e9 + 2; 
  while(lo < hi) { 
   int mid = (lo + hi) / 2; 
   if(check(mid)) { 
     hi = mid;  
   } else { 
     lo = mid + 1; 
   }
  }
  cout << (lo == 1e9 + 2 ? -1 : lo) << '\n';
  return 0;
}
