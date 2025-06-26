#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int mod = 1e9 + 7;

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

int get_next(vector<int> &pi, string &s, int pos, char c) {
  if (pos == sz(s)) pos = pi[pos];
  while (pos > 0 && c != s[pos]) pos = pi[pos];
  if (s[pos] == c) pos++;
  return pos;
} 


vector<vector<int>>nxt; 
vector<int>kmp; 
vector<vector<int64_t>>dyn[2][2]; 
string L, R, S; 

int64_t memo(const string &s, int pos, int state, int isEqual, int contain) { 
  if(pos == sz(s)) return contain; 
  int64_t &ret = dyn[isEqual][contain][pos][state]; 
  if(ret != -1) return ret; 
  ret = 0; 
  int bound = (isEqual ? s[pos] - '0' : 9); 
  for(int digit = 0; digit <= bound; digit++) { 
    int nextState = nxt[state][digit]; //get_next(kmp, S, state, char(digit + '0')); 
    (ret += memo(s, pos + 1, nextState, isEqual && (digit == bound), contain || nextState == sz(kmp) - 1)) %= mod; 
  }
  return ret; 
}

int checkSubstring() { 
  int start = 0; 
  for(int i = 0; i < sz(L); i++) { 
    start = nxt[start][L[i] - '0']; 
    if(start == sz(S)) return true; 
  }
  return false; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> L >> R >> S; 
  kmp = prefix_function(S);
  nxt.resize(sz(kmp) + 1, vector<int>(10)); 
  for(int i = 0; i < sz(kmp); i++) { 
    for(int j = 0; j < 10; j++) { 
      nxt[i][j] = get_next(kmp, S, i, char(j + '0')); 
    }
  }
  int64_t ret = 0; 
  for(int i = 0; i < 2; i++) { 
    for(int j = 0; j < 2; j++) { 
      dyn[i][j].resize(sz(R), vector<int64_t>(sz(kmp) + 1, -1)); 
    }
  }
  (ret += memo(R, 0, 0, true, false)) %= mod; 
  for(int i = 0; i < 2; i++) { 
    for(int j = 0; j < 2; j++) { 
      dyn[i][j].clear(); 
      dyn[i][j].resize(sz(L), vector<int64_t>(sz(kmp) + 1, -1)); 
    }
  }
  (ret += mod - memo(L, 0, 0, true, false)) %= mod; 
  (ret += checkSubstring()) %= mod; 
  cout << ret << '\n'; 
  return 0; 
}