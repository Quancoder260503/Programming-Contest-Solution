#include <bits/stdc++.h>

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 998244353; 

int main() { 
 int N, T; 
 for(cin >> T; T--; ) { 
  cin >> N;
  vector<int>a(N);
  for(auto &x : a) cin >> x; 
  int64_t ret = 1, sub = 1; 
  int mx_ = *max_element(a.begin(), a.end()); 
  int cnt = count(a.begin(), a.end(), mx_); 
  int cnt2 = count(a.begin(), a.end(), mx_ - 1); 
  for(int i = 1; i <= N; i++) { 
   ret = ret % MOD * i % MOD; 
   if(i != cnt2 + 1) sub = sub % MOD * i % MOD; 
  }
  if(cnt == 1) (ret = ret + MOD - sub) %= MOD; 
  cout << ret << '\n'; 
 } 
 return 0;
}