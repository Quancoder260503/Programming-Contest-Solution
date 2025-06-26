#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7; 

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

int get_next(vector<int> &pi, string &s, int pos, char c) {
  if (pos == sz(s)) pos = pi[pos];
  while (pos > 0 && c != s[pos]) pos = pi[pos];
  if (s[pos] == c) pos++;
  return pos;
} 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, M;  
  string S; 
  cin >> M >> N >> S;
  vector<int>kmp = prefix_function(S); 
  vector<int64_t> ways(N + 1);
  ways[M] = 1; 
  for(int i = M + 1; i <= N; i++) { 
    for(int j = 1; j <= M; j++) { 
      if(kmp[j] == 0) { 
        (ways[i] += ways[i - j]) %= mod; 
      }  
    }
  } 
  cout << ways[N] << '\n'; 
  return 0; 
}