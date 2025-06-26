#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const int maxn = 102; 
const int maxf = 10002; 

vector<double>dp[maxn][maxf]; 

double Comb(int a, int b) { 
 #define COMB__MAXA 10002
 #define COMB__MAXB 10002
 static double cache[COMB__MAXA][COMB__MAXB]; 
 if(b < 0 || a < b) return 0.;
 if(b == 0) return 1.; 
 if(cache[a][b] > 0.) return cache[a][b]; 
 double &ret = cache[a][b]; 
 ret = Comb(a - 1, b) + Comb(a - 1, b - 1); 
 return ret; 
} 

vector<double> f(int n, int m) { 
 if(n <= 0 || m <= 0) return {}; 
 if(sz(dp[n][m]) > 0) return dp[n][m];
 vector<double> &ret = dp[n][m]; 
 ret.resize(n, 1); 
 for(int i = 0; i <= n; i++) { 
  double Prob = Comb(n, n - i) * Comb(m - n, n - i) / Comb(m, n); 
  vector<double> next = f(n - i, m - n);
  for(int j = 0; j < sz(next); j++) ret[i + j] += Prob * next[j]; 
 } 
 return ret; 
}

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M; 
 cin >> N >> M; 
 cout << fixed << setprecision(10); 
 vector<double>ret = f(N, M); 
 double sum = 0; 
 for(int i = 0; i < sz(ret); i++) {
  sum += ret[i]; 
  cout << sum << '\n'; 
 } 
 return 0;
}