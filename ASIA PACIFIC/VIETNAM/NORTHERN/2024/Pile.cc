#include "bits/stdc++.h"

using namespace std; 

#pragma GCC optimize("O3")
#pragma GCC optimization("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define sz(x) int(x.size())

const int64_t oo = 1e12; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N, D, H; 
 cin >> N >> D >> H; 
 vector<int>h(N); 
 for(int i = 0; i < N; i++) { 
  cin >> h[i]; 
 }
 vector<int64_t>dp(N, oo); 
 dp[0] = h[0]; 
 for(int i = 1; i < N; i++) { 
  for(int j = i; i - j <= D && j >= 0; j--) {
    if(abs(h[i] - h[j]) <= H) { 
     dp[i] = min(dp[i], dp[j] + h[i]); 
    } 
  }
 }
 cout << (dp[N - 1] == oo ? -1 : dp[N - 1]) << '\n'; 
 return 0; 
}