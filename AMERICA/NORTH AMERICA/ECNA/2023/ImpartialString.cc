#include "bits/stdc++.h"

using namespace std; 

#define sz(x) (int)x.size()

const int maxf = 1000; 

int state[maxf][maxf][10]; 

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
  int Tc; 
  string A, S, T; 
  for(cin >> Tc; Tc--; ) { 
    memset(state, 0, sizeof(state)); 
    cin >> A >> S >> T; 
    vector<int>kmpS = prefix_function(S); 
    vector<int>kmpT = prefix_function(T); 
    queue<tuple<int, int, int>>q; 
    q.push({0, 0, 2}); 
    state[0][0][2] = true; 
    while(sz(q)) { 
      auto [state_S, state_T, diff] = q.front(); 
      q.pop(); 
      for(int j = 0; j < sz(A); j++) { 
        int next_S = get_next(kmpS, S, state_S, A[j]); 
        int next_T = get_next(kmpT, T, state_T, A[j]);
        int next_diff = diff; 
        if(next_S == sz(S)) {
          next_diff++;         
        }
        if(next_T == sz(T)) { 
          next_diff--; 
        }
        if(next_diff < 0 || next_diff > 4 || state[next_S][next_T][next_diff]) continue; 
        state[next_S][next_T][next_diff] = true; 
        q.push({next_S, next_T, next_diff}); 
      }       
    }
    int a = true, b = true; 
    for(int i = 0; i < sz(S); i++) { 
      for(int j = 0; j < sz(T); j++) { 
        if(state[i][j][2]) { 
         // cout << i << " " << j << " " << state[i][j][0] << " " << state[i][j][4] << '\n'; 
          if(state[i][j][0]) a = false; 
          if(state[i][j][4]) b = false; 
        }
      }
    }
    cout << (a || b) << '\n'; 
  }
  return 0; 
}