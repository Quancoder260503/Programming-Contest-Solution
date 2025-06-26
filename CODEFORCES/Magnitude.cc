#include "bits/stdc++.h"

using namespace std; 

const int MOD = 998244353; 
const int64_t oo = LLONG_MAX / 2; 

void solve() { 
 int N; 
 cin >> N; 
 int64_t sum = 0, c;
 vector<int64_t>a(N); 
 vector<int64_t> pw2(N + 1);
 pw2[0] = 1;  
 int64_t acc = 0, mn = 0, ret = 0;  
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  pw2[i + 1] = (pw2[i] * 2) % MOD; 
  acc += a[i];
  mn = min(mn, acc); 
 } 
 if(mn == 0) { 
  cout << pw2[N] << '\n'; 
  return; 
 }
 acc = 0; 
 for(int i = 0, cc = 0; i < N; i++) { 
  acc += a[i]; 
  if(acc == mn) { 
   (ret += pw2[N - i - 1 + cc]) %= MOD; 
  }
  if(acc >= 0) cc++; 
 }
 cout << ret << '\n'; 
 return;   
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { 
   solve(); 
  }
  return 0; 
}

