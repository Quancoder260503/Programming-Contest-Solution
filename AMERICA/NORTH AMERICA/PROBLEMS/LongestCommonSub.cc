#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())


int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n; 
  cin >> n; 
  vector<string>a(n); 
  for(auto &x : a) { 
   cin >> x; 
  }
  set<string>ms; 
  for(int i = 0; i < sz(a[0]); i++) { 
   for(int j = 1; j <= sz(a[0]) - i; j++) { 
    ms.insert(s[0].substr(i, j)); 
   } 
  }
  for(int i = 1; i < n; i++) { 
   set<string>mms; 
   for(auto &s : ms) { 
    if(a[i].contains(s)) { 
      mms.insert(s); 
    }
   }
   ms.swap(mms); 
  }
  int ret = 0; 
  for(auto &s : ms) { 
   ret = max(ret, sz(s)); 
  }
  cout << ret << '\n'; 
  return 0; 
}