#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

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
  set<int>ms; 
  unordered_map<int, int>mp; 
  for(int i = 0; i < k; i++) { 
   mp[a[i]]++; 
   if(mp[a[i]] == 1) { 
    ms.insert(a[i]); 
   } else if(mp[a[i]] > 1) { 
    ms.erase(a[i]); 
   }
  }
  if(sz(ms)) cout << *prev(ms.end()) << '\n';
  else cout << "Nothing\n"; 
  for(int i = k; i < n; i++) { 
   mp[a[i - k]]--; 
   if(mp[a[i - k]] == 1) { 
    ms.insert(a[i - k]); 
   } else if(mp[a[i - k]] > 1 || mp[a[i - k]] == 0) { 
    ms.erase(a[i - k]); 
   }
   mp[a[i]]++; 
   if(mp[a[i]] == 1) { 
    ms.insert(a[i]); 
   } else if(mp[a[i]] > 1) { 
    ms.erase(a[i]); 
   }
   if(sz(ms)) cout << *prev(ms.end()) << '\n';
   else cout << "Nothing\n"; 
  } 
  return 0; 
}
