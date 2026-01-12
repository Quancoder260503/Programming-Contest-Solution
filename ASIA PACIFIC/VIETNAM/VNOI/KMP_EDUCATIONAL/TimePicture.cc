#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 360000;

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
  cin >> N ; 
  vector<int>a(N); 
  vector<int>b(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i];  
  }
  for(int i = 0; i < N; i++) { 
   cin >> b[i]; 
  }
  sort(b.begin(), b.end()); 
  sort(a.begin(), a.end()); 
  for(int i = 0; i < N; i++) { 
   a.push_back(a[i]); 
  }
  vector<int>cc; 
  for(int i = 0; i < N; i++) { 
   cc.push_back((b[i] - b[(i + 1) % N] + MOD) % MOD); 
  }
  cc.push_back(100000000); 
  for(int i = 0; i < 2 * N; i++) { 
   cc.push_back((a[i] - a[(i + 1) % (2 * N)] + MOD) % MOD); 
  }
  vector<int>pi = prefix_function(cc); 
  for(int j = 2 * N; j < sz(pi); j++) { 
   if(pi[j] == N) { 
    cout << "YES\n"; 
    return 0; 
   }
  }
  cout << "NO\n"; 
  return 0; 
}
