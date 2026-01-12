#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

vector<int> prefix_function(const string &s) {
  int n = sz(s); 
  vector<int> pi(n + 1);
  for (int i = 2; i <= n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i - 1] != s[j]) j = pi[j];
    if (s[i - 1] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

int get_next(vector<int>&pi, string &s, int pos, char c) { 
  if(pos == sz(s)) pos = pi[pos]; 
  while(pos > 0 && c != s[pos]) pos = pi[pos]; 
  if(s[pos] == c) pos++;
  return pos; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S, T; 
  while(cin >> S >> T) { 
    vector<int>kmp = prefix_function(T); 
    vector<vector<int>> dyn(sz(S) + 1, vector<int> (sz(kmp) + 1, -1));
    dyn[0][0] = 0; 
    for(int i = 0; i < sz(S); i++) { 
      for(int state = 0; state < sz(kmp); state++) { 
        if(dyn[i][state] == -1) continue; 
        int next_state = get_next(kmp, T, state, S[i]);
        if(next_state < sz(T)) { 
          if(dyn[i + 1][next_state] == -1) dyn[i + 1][next_state] = dyn[i][state]; 
          else dyn[i + 1][next_state] = min(dyn[i + 1][next_state], dyn[i][state]); 
        }
        if(dyn[i + 1][state] == -1) dyn[i + 1][state] = 1 + dyn[i][state]; 
        else dyn[i + 1][state] = min(dyn[i + 1][state], 1 + dyn[i][state]); 
      }
    }
    int ret = sz(S) + 1; 
    for(int i = 0; i < sz(kmp); i++) { 
      if(dyn[sz(S)][i] == -1) continue; 
      ret = min(ret, dyn[sz(S)][i]); 
    }
    cout << ret << '\n';  
  }
  return 0; 
}