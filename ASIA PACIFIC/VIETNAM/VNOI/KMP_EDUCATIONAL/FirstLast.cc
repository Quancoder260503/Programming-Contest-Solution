#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

vector<int> prefix_function(const string &s) { 
 int n = sz(s); 
 vector<int>pi(n); 
 for(int i = 1; i < n; i++) { 
  int j = pi[i - 1]; 
  while(j > 0 && s[i] != s[j]) j = pi[j - 1]; 
  if(s[i] == s[j]) j++; 
  pi[i] = j; 
 }
 return pi;    
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N; 
  string S; 
  cin >> N >> S; 
  vector<int>pi = prefix_function(S);
  vector<int>cnt(N + 1); 
  for(int j = 0; j < N; j++) { 
   cnt[pi[j]]++; 
  }
  for(int j = N - 1; j > 0; j--) { 
   cnt[pi[j - 1]] += cnt[j]; 
  }
  for(int j = 0; j <= N; j++) { 
   cnt[j]++; 
  }
  int j = N - 1; 
  vector<pair<int, int>>ret; 
  while(j > 0 && pi[j] > 0) { 
   ret.push_back({pi[j], cnt[pi[j]]}); 
   j = pi[j] - 1;  
  }
  ret.push_back({N, 1}); 
  sort(ret.begin(), ret.end()); 
  cout << sz(ret) << '\n'; 
  for(auto [u, v] : ret) { 
   cout << u << " " << v << '\n'; 
  }
  return 0; 
}
