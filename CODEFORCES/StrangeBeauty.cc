#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

vector<int>d[200005]; 
int dp[200005]; 

void init() {
 for(int i = 1; i < 200005; i++) { 
  for(int j = 2 * i; j < 200005; j += i) { 
    d[j].push_back(i); 
  }
 } 
 return; 
}

void solve() { 
 int N; 
 cin >> N; 
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 memset(dp, -1, sizeof(dp)); 
 sort(a.begin(), a.end()); 
 for(int i = 0; i < N; i++) { 
  if(dp[a[i]] == -1) dp[a[i]] = 1; 
  else dp[a[i]]++;  
  for(auto &x : d[a[i]]) { 
   if(dp[x] == -1) continue; 
   dp[a[i]] = max(dp[a[i]], dp[x] + 1); 
  }
 }
 int ret = 0; 
 for(int i = 0; i < N; i++) {
  ret = max(ret, dp[a[i]]); 
 }
 cout << N - ret << '\n'; 
 return; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 init(); 
 int T; 
 for(cin >> T; T--; ) { solve(); }
 return 0; 
}