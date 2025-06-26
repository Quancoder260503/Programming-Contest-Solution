#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9; 

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
 int N; 
 cin >> N; 
 vector<string>s(N); 
 for(int i = 0; i < N; i++) { 
  cin >> s[i];
 }
 sort(s.begin(), s.end()); 
 s.erase(unique(s.begin(), s.end()), s.end()); 
 N = sz(s); 
 vector<vector<int>>g(N, vector<int>(N)); 
 vector<vector<int>>dp(N, vector<int>(1 << N, oo)); 
 vector<int>marked(N); 
 for(int i = 0; i < N; i++) { 
  for(int j = 0; j < N; j++) { 
   if(i == j) continue; 
   string cc = s[i] + "/" + s[j];
   vector<int>kmp = prefix_function(cc);
   for(int k = sz(s[i]) + 1; k < sz(kmp); k++) { 
    if(kmp[k] == sz(s[i])) {
     marked[i] = true;  
     break; 
    }
   }
   if(marked[i]) continue; 
   g[j][i] = sz(s[i]) - kmp.back(); 
   // what is the largest prefix of s[i] that matches the suffix of s[j]
  }
 } 
 int Smask = 0; 
 for(int i = 0; i < N; i++) {
  if(marked[i]) continue;
  Smask |= (1 << i);  
  dp[i][1 << i] = sz(s[i]); 
 }
 for(int mask = 0; mask < (1 << N); mask++) { 
  for(int i = 0; i < N; i++) { 
   if(mask & (1 << i)) { 
    for(int j = 0; j < N; j++) { 
     if((mask & (1 << j)) || marked[j]) continue; 
     dp[j][mask | (1 << j)] = min(dp[j][mask | (1 << j)], dp[i][mask] + g[i][j]); 
    }
   }
  }
 }
 int ret = oo; 
 for(int i = 0; i < N; i++) {
  ret = min(ret, dp[i][Smask]); 
 }
 cout << ret << '\n'; 
 return 0; 
}