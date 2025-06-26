#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 4000; 

int dyn[2][maxf]; 

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
  cin >> S >> T; 
  if(sz(S) < sz(T)) { 
    cout << 0 << '\n'; 
    return 0; 
  }
  set<char>c; 
  for(int i = 0; i < sz(T); i++) { 
    c.insert(T[i]); 
  }
  vector<int>kmp = prefix_function(T); 
  memset(dyn, -1, sizeof(dyn)); 
  dyn[0][0] = 0; 
  for(int i = 0; i < sz(S); i++) { 
    fill(dyn[(i + 1) & 1], dyn[(i + 1) & 1] + sz(T) + 1, -1); 
    for(int j = 0; j <= sz(T); j++) if(dyn[i & 1][j] != -1) { 
      if(S[i] != '?') { 
        int state = get_next(kmp, T, j, S[i]); 
        dyn[(i + 1) & 1][state] = max(dyn[(i + 1) & 1][state], dyn[i & 1][j] + (state == sz(T))); 
      }
      else { 
        for(auto ch : c) { 
          int state = get_next(kmp, T, j, ch); 
          dyn[(i + 1) & 1][state] = max(dyn[(i + 1) & 1][state], dyn[i & 1][j] + (state == sz(T))); 
        }
      }
    } 
  }
  int ret = 0; 
  for(int i = 0; i <= sz(T); i++) { 
    ret = max(ret, dyn[sz(S) & 1][i]); 
  }
  cout << ret << '\n'; 
  return 0; 
}