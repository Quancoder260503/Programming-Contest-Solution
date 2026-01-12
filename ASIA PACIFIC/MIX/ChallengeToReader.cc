#include <vector> 
#include <iostream> 

using namespace std; 

int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 int T, x;  
 for(cin >> T; T--; ) { 
  cin >> x; 
  for(int cand = 1; cand <= 500; cand++) { 
    int total = cand * (cand + 1) / 2 - x; 
    if(total < 0 || total % 2 == 1) continue;
    total = total / 2;  
    int curr = total; 
    vector<int>vis(cand + 1); 
    for(int i = cand; i > 1; i--) {
     if(total < i) continue; 
     vis[i] = 1; 
     total = total - i;  
    } 
    if(total > 0) {
     fill(vis.begin(), vis.end(), 0);   
     for(int i = cand; i > 1; i--) {
      if(total < i) continue; 
      vis[i] = 1; 
      total = total - i;  
     }
     if(total > 0) { 
      goto here; 
     }   
    }
    cout << cand << '\n'; 
    cout << 1; 
    for(int j = 2; j <= cand; j++) { 
      cout << (!vis[j] ? "+" : "-") << j; 
    }
    cout << '\n'; 
    goto done;
  here:; 
  } 
 done:;
  // break;  
 }
 return 0; 
}