#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const double oo = 1e20; 

int main() {
  int N1, N2, L; 
  double H; 
  cin >> H >> N1 >> N2 >> L;
  vector<int>a(N1), b(N2); 
  for(int i = 0; i < N1; i++) { 
    cin >> a[i]; 
  } 
  for(int i = 0; i < N2; i++) { 
    cin >> b[i]; 
  } 
  sort(a.rbegin(), a.rend()); 
  sort(b.rbegin(), b.rend()); 
  vector<vector<double>>dp(N1 + N2 + 1, vector<double>(L + 1, oo)); 
  dp[0][0] = H; 
  for(int i = 0; i < N1; i++) { 
   for(int j = 0; j <= L; j++) { 
    dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]); 
    if(j < L) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] * (1 - 1. * a[i] / 100)); 
   } 
  } 
  for(int i = N1; i < N2 + N1; i++) { 
   for(int j = 0; j <= L; j++) { 
    dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]); 
    if(j < L) dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] - b[i - N1]); 
   } 
  }
  cout << fixed << setprecision(10) << dp[N1 + N2][L] << '\n'; 
  return 0;
}