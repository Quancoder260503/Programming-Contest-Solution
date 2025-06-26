#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())
 
const int MAXN = 1e6 + 2; 
 
int64_t ans[MAXN], cnt[MAXN], acc[MAXN]; 
 
class CountingRhyme { 
 public : 
  void solve() { 
   int N; 
   cin >> N;
   for(int i = 0, x; i < N; i++) { 
    cin >> x; 
    cnt[x]++;
   }
   if(cnt[1] > 0) { 
    cout << 0 << '\n'; 
   } else { 
    int64_t ret = 0;  
    for(int i = N; i > 0; i--) { 
     for(int j = i; j <= N; j += i) { 
      acc[i] += cnt[j]; 
      ans[i] -= ans[j];  
     }
     ans[i] += 1LL * acc[i] * (acc[i] - 1) / 2;
    }
    for(int i = 1; i <= N; i++) { 
     if(!cnt[i]) continue; 
     for(int j = 2 * i; j <= N; j += i) { 
      cnt[j] = 1;
     }
    }
    for(int i = 0; i <= N; i++) { 
     if(cnt[i]) ret += ans[i]; 
    }
    ret = 1LL * N * (N - 1) / 2 - ret; 
    cout << ret << '\n'; 
   } 
   for(int i = 0; i <= N; i++) { 
    ans[i] = cnt[i] = acc[i] = 0; 
   }
   return; 
  }
}; 
 
int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  CountingRhyme task; 
  int T; 
  cin >> T; 
  for(int i = 0; i < T; i++) { 
   task.solve(); 
  }
  return 0; 
}