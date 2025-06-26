#include "bits/stdc++.h"

using namespace std;

const int MOD = 998244353; 

class Transformation { 
  public : 
   void solve() {
    int N; 
    cin >> N;
    vector<int>a(N), vis(N); 
    for(int i = 0; i < N; i++) { 
     cin >> a[i]; 
     a[i]--; 
    }
    int cc = 0; 
    map<int, int>counter; 
    for(int i = 0; i < N; i++) { 
     if(vis[i]) continue; 
     int st = i, cycle = 0; 
     while(!vis[st]) { 
       vis[st] = true; 
       st = a[st]; 
       cycle++; 
     }
     int offset = 0; 
     while((cycle % 2) == 0) { 
      cycle = cycle / 2; 
      offset++; 
     }
     cc = max(cc, offset); 
     if(cycle <= 1) continue;
     int p = 1, curr = 2; 
     while(curr != 1) { 
      curr = (curr * 2) % cycle; 
      p++; 
     } 
     for(int prime = 2; prime * prime <= p; prime++) { 
      if(p % prime == 0) { 
        int cnt = 0; 
        while(p % prime == 0) { 
         p = p / prime; 
         cnt++; 
        }
        counter[prime] = max(counter[prime], cnt); 
      }
     }
     if(p > 1) { 
      counter[p] = max(counter[p], 1); 
     }
    }
    int64_t ans = 1; 
    for(auto [p, cnt] : counter) { 
    // cout << p << " " << cnt << '\n'; 
     for(int j = 0; j < cnt; j++) { 
       ans = ans % MOD * p % MOD; 
     }
    }
    ans = (ans + cc) % MOD; 
    cout << ans << '\n'; 
    return; 
   }
}; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 Transformation task; 
 task.solve(); 
 return 0; 
}