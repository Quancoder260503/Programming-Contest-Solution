#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 vector<int>vis(2000001); 
 for(int i = 2; i < sz(vis); i++) { 
  if(vis[i]) continue; 
  for(int j = 2 * i; j < sz(vis); j += i) { 
   vis[j] = true; 
  }
 }
 vis[1] = true; 
 int N; 
 cin >> N; 
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 } 
 vector<int>ret; 
 for(int i = 0; i < N; i++) { 
  //intven = 0, odd = 0, ones = 0; 
  vector<int>even, odd; 
  int ones = 0;
  for(int j = 0; j < N; j++) { 
   if(i == j) continue; 
   if(!vis[a[i] + a[j]]) { 
    ones += (a[j] == 1); 
    (a[j] % 2 == 0 ? even : odd).push_back(a[j]); 
   }
  }
  if(a[i] % 2 == 0) { 
    if(ones > 0 && sz(ret) < ones + 1) { 
     vector<int>cc; 
     for(int j = 0; j < ones; j++) { cc.push_back(1); }
     cc.push_back(a[i]); 
     swap(ret, cc); 
    }
    if(!vis[a[i]]) { 
     if(sz(ret) < 1 + min(sz(odd), 1)) { 
      ret.clear(); 
      ret.push_back(a[i]); 
      if(sz(odd)) ret.push_back(odd.back()); 
     }
    } else if(sz(even) > 0) {
     if(sz(ret) < 2) { 
       ret.clear(); 
       ret.push_back(a[i]); 
       ret.push_back(even.back()); 
     }
    }  
  } else { 
   if(!vis[a[i]]) { 
    if(sz(ret) < 1 + min(sz(even), 1)) { 
     ret.clear(); 
     ret.push_back(a[i]); 
     if(sz(even)) ret.push_back(even.back()); 
    }
   } else if(sz(even) > 0) {
    if(sz(ret) < 2) { 
      ret.clear(); 
      ret.push_back(a[i]); 
      ret.push_back(even.back()); 
    }
   } else if (a[i] == 1) {
    if(sz(ret) < ones + 1) { 
     vector<int>cc; 
     for(int j = 0; j < ones; j++) { cc.push_back(1); }
     cc.push_back(a[i]); 
     swap(ret, cc); 
    }
   } 
  }
 }
 if(sz(ret) == 0) { 
  cout << 1 << '\n' << a.back() << '\n'; 
  return 0; 
 }
 cout << sz(ret) << '\n'; 
 for(auto &x : ret) cout << x << " "; 
 cout << '\n'; 
 return 0;
}