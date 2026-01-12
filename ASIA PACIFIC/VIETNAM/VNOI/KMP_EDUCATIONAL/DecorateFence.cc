#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

vector<int> prefix_function(const vector<int>&s) { 
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
  int N, M; 
  cin >> N >> M; 
  vector<int>a(N), b(M), diff_a(N - 1), diff_b(M - 1); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  for(int i = 0; i < M; i++) { 
   cin >> b[i]; 
  }
  for(int i = 0; i + 1 < N; i++) { 
   diff_a[i] = a[i] - a[i + 1]; 
  }
  for(int i = 0; i + 1 < M; i++) { 
   diff_b[i] = b[i] - b[i + 1]; 
  }
  vector<int>cc; 
  for(int i = 0; i < M - 1; i++) { 
   cc.push_back(diff_b[i]); 
  } 
  cc.push_back(100000000); 
  for(int i = 0; i < N - 1; i++) { 
   cc.push_back(diff_a[i]); 
  }
  vector<int>pi = prefix_function(cc);
  vector<int64_t>dp(N + 1, 0);  
  for(int j = N - 1; j >= 0; j--) { 
   (dp[j] += dp[j + 1]) %= MOD; 
   if(pi[M + j - 1] == M - 1 && a[j - M + 1] >= b[0]) { 
    (dp[j - M + 1] += 1 + dp[j + 1]) %= MOD; 
   } 
 //  cout << dp[j] << '\n'; 
  }
  cout << dp[0] << '\n'; 
  return 0; 
}
