#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 998244353;

class Ksubsequence {
public:
 int N; 
 string S; 
 int64_t memo(int pos, int last_char, vector<vector<int64_t>>&dp, vector<vector<int>>&nxt) {
  int64_t &ret = dp[pos][last_char];
  if (ret != -1) return ret;
  ret = 0;
  for (int ch = 0; ch < 26; ch++) {
   if (nxt[pos][ch] != N + 1) {
    if (nxt[pos][last_char] > N || nxt[pos][last_char] >= nxt[pos][ch]) {
     ret += memo(nxt[pos][ch], ch, dp, nxt);
     ret %= MOD;
    }
   }
  }
  ret += (nxt[pos][last_char] == N + 1);
  ret %= MOD;
  return ret;
 } 
 void solve(int K) {
  cin >> N >> S;
  S = " " + S;
  vector<vector<int64_t>>dp;
  vector<vector<int>> nxt(N + 7, vector<int>(26, N + 1));
  for (int i = 0; i <= N; i++) {
   for (int j = i - 1; j >= 0; j--) {
    nxt[j][S[i] - 'a'] = i;
    if (S[i] == S[j]) break;
   }
  }
  if (K == 1) {
   dp.resize(N + 7, vector<int64_t>(26, -1));
   int64_t ans = 0;
   for (int ch = 0; ch < 26; ch++) {
    if (nxt[0][ch] != N + 1) {
     (ans += memo(nxt[0][ch], ch, dp, nxt)) %= MOD;
    }
   }
   cout << ans << '\n';
  } else {
   dp.resize(N + 7, vector<int64_t>(3, 0));
   vector<int>last(N + 1, -1); 
   vector<int>cc(26); 
   for(int i = 1; i <= N; i++) { 
    last[i] = cc[S[i] - 'a']; 
    cc[S[i] - 'a'] = i; 
   }
   int64_t ans = 0; 
   for(int c = 0; c < 26; c++) { 
    int pos = nxt[0][c]; 
    if(pos != N + 1) { 
     dp[pos][0] += 1; 
     if(nxt[pos][c] != N + 1) { 
      dp[nxt[pos][c]][1] += 1; 
     }
    }
   }
   for(int i = 1; i <= N; i++) { 
    int curr = S[i] - 'a'; 
    if(nxt[i][curr] == N + 1) { 
      (ans += dp[i][1]) %= MOD; 
      (ans += dp[i][2]) %= MOD; 
    }
    for(int c = 0; c < 26; c++) { 
     if(nxt[i][c] != -1 && nxt[i][c] <= nxt[i][curr]) { 
      (dp[nxt[i][c]][0] += dp[i][0]) %= MOD; 
      (dp[nxt[i][c]][2] += dp[i][2]) %= MOD; 
     }
    } 
    for(int c = 0; c < 26; c++) { 
     if(c == curr) continue; 
     int next_pos = nxt[i][c]; 
     if(next_pos == N + 1) continue; 
     int next_pos_2 = nxt[next_pos][c]; 
     if(next_pos_2 == N + 1) continue; 
     if(nxt[i][curr] > next_pos_2) { 
      (dp[next_pos_2][1] += dp[i][0]) %= MOD; 
     } 
    }
    int prev = last[i]; 
    if(prev == -1) continue; 
    for(int c = 0; c < 26; c++) { 
     if(c == curr) continue;
     if(nxt[prev][c] == nxt[i][c] && nxt[i][c] <= N && nxt[i][c] <= nxt[i][curr]) { 
      (dp[nxt[i][c]][2] += dp[i][1]) %= MOD; 
     }
    }
   }
   cout << ans << '\n'; 
  }  
  return;
 }
};

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 Ksubsequence task;
 int T, K;
 for (cin >> T >> K; T--;) {
  task.solve(K);
 }
 return 0;
}