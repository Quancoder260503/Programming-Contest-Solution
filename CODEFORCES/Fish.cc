#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<vector<double>>Prob(N, vector<double>(N)); 
 for(int i = 0; i < N; i++) {  
  for(int j = 0; j < N; j++) { 
   cin >> Prob[i][j]; 
  } 
 } 
 vector<double>dp(1 << N, -1); 
 function<double(int)>F = [&](int mask) { 
  if(mask == (1 << N) - 1) return 1.; 
  double &ret = dp[mask]; 
  if(ret >= 0) return ret; 
  ret = 0; 
  int numAlive = __builtin_popcount(mask); 
  for(int alive = 0; alive < N; alive++) { 
   if(mask & (1 << alive)) { 
    for(int killed = 0; killed < N; killed++) { 
     if(mask & (1 << killed)) continue; 
     double den = numAlive * (numAlive + 1) / 2; 
     ret += F(mask | (1 << killed)) / den * Prob[alive][killed]; 
    } 
   } 
  } 
  return ret; 
 }; 
 cout << fixed << setprecision(7); 
 for(int i = 0; i < N; i++) { 
  cout << F(1 << i) << " "; 
 } 
 return 0; 
}
