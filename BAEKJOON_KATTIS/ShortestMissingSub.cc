#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e7; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S, T;
  cin >> T >> S;
  set<char>ms; 
  for(int i = 0; i < sz(T); i++) { 
    ms.insert(T[i]); 
  }
  S = " " + S;
  int N = sz(S); 
  vector<vector<int>>next(N, vector<int>(26, N)); 
  for(int i = 1; i < sz(S); i++) { 
    for(int j = i - 1; j >= 0; j--) {
      next[j][S[i] - 'a'] = i; 
      if(S[i] == S[j]) break; 
    }
  }
  vector<int>dp(N + 1, oo); 
  dp[N] = 0; 
  for(int i = N - 1; i >= 0; i--) { 
    for(auto c : ms) {
      dp[i] = min(dp[i], dp[next[i][c - 'a']] + 1); 
    }
  }
  int Q;
  for(cin >> Q; Q--; ) { 
    string s; 
    cin >> s;
    int flag = true;  
    for(int j = 0; j < sz(s); j++) {
      if(!ms.count(s[j])) { 
        flag = false;
        break; 
      }
    }
    if(!flag) {
      cout << flag << '\n'; 
      continue; 
    }
    int start = 0; 
    for(int i = 0; i < sz(s) && start < N; i++) {
      start = next[start][s[i] - 'a']; 
    }
    cout << (start == N && sz(s) == dp[0]) << '\n'; 
  }
  return 0; 
}