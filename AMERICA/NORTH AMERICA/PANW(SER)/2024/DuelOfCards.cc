#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
 int N; 
 cin >> N; 
 vector<int>vis(2 * N); 
 for(int i = 0, x; i < N; i++) {
  cin >> x;  
  vis[--x] = true; 
 }
 set<int>s; 
 for(int i = 0; i < 2 * N; i++) { 
  if(vis[i]) continue; 
  s.insert(i);
 }
 int ret = 0; 
 for(int i = 0; i < 2 * N ; i++) { 
  if(vis[i]) { 
   auto it = s.lower_bound(i); 
   if(it != s.end()) { 
    s.erase(it); 
   } else { 
    s.erase(*prev(s.end())); 
    ret++; 
   }
  }
 }
 cout << ret << ' '; 
 for(int i = 0; i < 2 * N; i++) { 
  if(vis[i]) continue; 
  s.insert(i);
 }
 ret = 0; 
 for(int i = 2 * N - 1; i >= 0; i--) { 
  if(vis[i]) { 
   auto it = s.lower_bound(i); 
   if(it != s.begin()) { 
    --it; 
    ret++; 
    s.erase(it); 
   } else { 
    s.erase(it); 
   }
  }
 }
 cout << ret << '\n';
 return 0; 
}