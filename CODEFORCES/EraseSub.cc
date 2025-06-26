#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int f(const string &s, const string &a, const string &b, vector<vector<int>> &next) {
  vector<vector<int>>dyn(sz(a) + 1, vector<int>(sz(b) + 1, sz(s) + 1));
  for(int i = 0; i <= sz(a); i++) {
    for(int j = 0; j <= sz(b); j++) { 
      if(i == 0 && j == 0) dyn[i][j] = 0; 
      else {
        if(i > 0) dyn[i][j] = min(dyn[i][j], next[dyn[i - 1][j]][a[i - 1] - 'a']);
        if(j > 0) dyn[i][j] = min(dyn[i][j], next[dyn[i][j - 1]][b[j - 1] - 'a']);  
      }
    }
  }
  return dyn[sz(a)][sz(b)] <= sz(s); 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Tc;
  string S, T; 
  for(cin >> Tc; Tc--; ) { 
    cin >> S >> T;
    S = " " + S;
    int N = sz(S);
    vector<vector<int>>nxt(N + 2, vector<int>(26, N + 2)); 
    for(int i = 1; i < N; i++) { 
      for(int j = i - 1; j >= 0; j--) {
        nxt[j][S[i] - 'a'] = i;
        if(S[i] == S[j]) break; 
      }
    }
    int ret = false; 
    for(int i = 1; i <= sz(T); i++) { 
      string sA = T.substr(0, i), sB = T.substr(i, sz(T) - i);
      if(f(S, sA, sB, nxt)) {
        ret = true;
        break; 
      } 
    }
    cout << (ret ? "YES" : "NO") << '\n'; 
  }  
  return 0; 
}
