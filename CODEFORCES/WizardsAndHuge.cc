#include <bits/stdc++.h> 

using namespace std; 

const int offset = 301; 

int main() { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K, L; 
 cin >> N >> L >> K;
 vector<vector<vector<double>>>dp(N + 1, 
                                  vector<vector<double>>(N + 2, 
                                  vector<double>(2 * offset + 1, 0.)));
 dp[0][0][offset + K] = 1.; 
 vector<double>Prob(N + 1);
 vector<int>a(N + 1); 
 for(int i = 1; i <= N; i++) { 
  cin >> Prob[i]; 
  Prob[i] /= 100.; 
 } 
 for(int i = 1; i <= N; i++) { 
  cin >> a[i]; 
 } 
 for(int ind = 1; ind <= N; ind++) {
  for(int wins = 0; wins <= N; wins++) { 
   for(int cap = 0; cap <= 2 * offset; cap++) {
    dp[ind][wins + 1][max(0, min(2 * offset, cap + a[ind]))] += Prob[ind] * dp[ind - 1][wins][cap]; 
    dp[ind][wins][cap] += (1. - Prob[ind]) * dp[ind - 1][wins][cap]; 
   } 
  } 
 }
 double ret = 0; 
 for(int i = L; i <= N; i++) { 
  for(int cap = offset; cap <= 2 * offset; cap++) { 
   ret += dp[N][i][cap]; 
  } 
 } 
 cout << fixed << setprecision(10) << ret << '\n'; 
 return 0;
}
