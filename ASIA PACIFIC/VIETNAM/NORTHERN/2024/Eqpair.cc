#include "bits/stdc++.h"

using namespace std; 

int64_t mp[1000002]; 

const int MOD = 1e9 + 7;

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N;
 cin >> N; 
 int64_t ret = 0; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  ret += mp[x]; 
  mp[x]++; 
 }
 ret %= MOD; 
 cout << ret << '\n'; 
 return 0; 
}