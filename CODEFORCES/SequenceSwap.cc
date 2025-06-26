#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int oo = 1e9; 

class SequenceSwap { 
  public:   
   void solve() { 
    int N, X;
    cin >> N >> X; 
    vector<int>a(N);
    int mem_size = X;  
    for(int i = 0; i < N; i++) { 
     cin >> a[i]; 
     mem_size = max(mem_size, a[i]); 
    } 
    if(N == 1) { 
     cout << 0 << '\n'; 
     return; 
    }
    vector<vector<vector<int>>>dp(2, vector<vector<int>>(mem_size + 1, vector<int>(mem_size + 1, oo))); 
    dp[0][a[0]][X] = 0; 
    if(a[0] > X) dp[0][X][a[0]] = 1; 
    int ans = oo; 
    for(int pos = 0; pos + 1 < N; pos++) { 
     for(int prev_num = 0; prev_num <= mem_size; prev_num++) { 
      for(int curr_x = 0; curr_x <= mem_size; curr_x++) {
        dp[(pos + 1) & 1][prev_num][curr_x] = oo; 
      }
     }
     for(int prev_num = 0; prev_num <= mem_size; prev_num++) { 
      for(int curr_x = 0; curr_x <= mem_size; curr_x++) { 
        if(prev_num <= a[pos + 1]) { 
          dp[(pos + 1) & 1][a[pos + 1]][curr_x] = min(dp[(pos + 1) & 1][a[pos + 1]][curr_x], 
                                                      dp[pos & 1][prev_num][curr_x]); 
        } 
        if(prev_num <= curr_x && curr_x < a[pos + 1]) { 
          dp[(pos + 1) & 1][curr_x][a[pos + 1]] = min(dp[(pos + 1) & 1][curr_x][a[pos + 1]],
                                                      dp[pos & 1][prev_num][curr_x] + 1); 
        } 
        if(pos == N - 2) ans = min({ans, dp[(pos + 1) & 1][a[pos + 1]][curr_x], dp[(pos + 1) & 1][curr_x][a[pos + 1]]}); 
      }
     }
    }
    cout << (ans == oo ? -1 : ans) << '\n'; 
    return;  
   }
};


int main(void) {  
 SequenceSwap seq; 
 int T; 
 for(cin >> T; T--; ) { seq.solve(); }
 return 0; 
}