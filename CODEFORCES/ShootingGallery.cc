#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<array<double, 4>>shoot(N); 
 for(int i = 0; i < N; i++) { 
  cin >> shoot[i][0] >> shoot[i][1] >> shoot[i][2] >> shoot[i][3]; 
 } 
 vector<double>dp(N); 
 sort(shoot.begin(), shoot.end(), [&](array<double, 4>a, array<double, 4>b) { 
  return a[2] < b[2]; 
 }); 
 for(int i = 0; i < N; i++) { 
  dp[i] = shoot[i][3]; 
  for(int j = 0; j < i; j++) {
   if(hypot(shoot[i][0] - shoot[j][0], shoot[i][1] - shoot[j][1]) + shoot[j][2] <= shoot[i][2]) { 
    dp[i] = max(dp[i], shoot[i][3] + dp[j]); 
   } 
  } 
 } 
 cout << fixed << setprecision(10) << *max_element(dp.begin(), dp.end()) << '\n'; 
 return 0; 
}
