#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int MOD = 998244353;
 
int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N;
 vector<int>a(N); 
 map<int, int>mp;
 vector<int>last(N, -1); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i];  
 }
 for(int i = N - 1; i >= 0; i--) { 
  if(!mp.count(a[i])) mp[a[i]] = i; 
  last[i] = mp[a[i]]; 
 } 
 int opt = -1; 
 int64_t ans = 1; 
 for(int i = 0; i < N - 1; i++) { 
  opt = max(opt, last[i]); 
  if(opt == i) { 
   (ans = ans * 2) %= MOD; 
  }
 }
 cout << ans << '\n'; 
 return 0; 
} 