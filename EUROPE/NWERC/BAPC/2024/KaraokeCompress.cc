#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int BASE = 1009; 
const int64_t MOD = 9000000000000007L; 

class Karaoke { 
  public:   
   void solve() { 
    string S; 
    cin >> S;  
    int N = sz(S); 
    vector<vector<int64_t>>hash_code(N + 1, vector<int64_t>(N + 1)); 
    for(int i = 0; i < N; i++) { 
     int64_t v = 0; 
     for(int j = i; j < N; j++) { 
      v = (1LL * BASE % MOD * v % MOD + (S[j] - 'a' + 1)) % MOD; 
      hash_code[i][j + 1] = v; 
     }
    }
    int ret = N + 1; 
    for(int len = 2; len < N; len++) { 
     unordered_map<int64_t, int>counter, next_pos; 
     for(int pos = 0; pos <= N - len; pos++) { 
      int64_t v = hash_code[pos][pos + len];
      if(next_pos[v] > pos) continue; 
      next_pos[v] = len + pos;  
      counter[v]++;  
     }
     for(auto [_, num] : counter) { 
      ret = min(ret, N - num * len + num + len); 
     }
    }
    cout << ret << '\n'; 
    return;  
   }
};


int main(void) {  
 Karaoke kara; 
 kara.solve(); 
 return 0; 
}