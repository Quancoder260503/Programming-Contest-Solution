#include "bits/stdc++.h"

using namespace std;  

#define sz(x) int(x.size())

const int64_t oo = 1e9; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T, n;
  int64_t m;  
  for(cin >> T; T--; ) { 
   cin >> n >> m; 
   vector<pair<int, int>>a(n); 
   for(int i = 0; i < n; i++) { 
    cin >> a[i].first >> a[i].second; 
   }
   sort(a.begin(), a.end()); 
   auto check = [&](int64_t median) { 
    int64_t s = 0, cnt = 0; 
    vector<int>v; 
    for(int i = 0; i < sz(a); i++) { 
     if(a[i].second < median) { 
      s += a[i].first; 
     } else if(a[i].first >= median) { 
      s += a[i].first; 
      cnt++; 
     } else { 
      v.push_back(a[i].first);   
     }
    }
    int64_t c = max(0LL, (n + 1) / 2 - cnt);
    if(c > v.size()) return false;  
    for(int i = 0; i < v.size(); i++) { 
     if(i < sz(v) - c) { 
      s += v[i]; 
     } else { 
      s += median; 
     }
    }
  //  cout << s << " " << m << '\n'; 
    return s <= m;  
   }; 
   int64_t lo = 0, hi = oo;
   while(lo < hi) { 
    int64_t mid = (lo + hi + 1) / 2; 
    if(check(mid)) { 
     lo = mid; 
    } else { 
      hi = mid - 1; 
    }
   }
   cout << lo << '\n'; 
  }
  return 0; 
}
