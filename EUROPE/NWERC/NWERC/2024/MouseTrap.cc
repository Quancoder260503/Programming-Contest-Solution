#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const double oo = 1e50; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<pair<double, double>>pts(N); 
 for(int i = 0; i < N; i++) { 
  cin >> pts[i].first >> pts[i].second; 
 }
 vector<vector<double>>suffix_x(N, vector<double>(3)), suffix_y(N, vector<double>(3)); 
 for(int i = N - 1; i >= 0; i--) { 
  suffix_x[i][0] = pts[i].first * N        + (i + 1 < N ? suffix_x[i + 1][0] : 0);
  suffix_x[i][1] = pts[i].first * (-2 * i) + (i + 1 < N ? suffix_x[i + 1][1] : 0); 
  suffix_x[i][2] = pts[i].first            + (i + 1 < N ? suffix_x[i + 1][2] : 0);    
  suffix_y[i][0] = pts[i].second * N        + (i + 1 < N ? suffix_y[i + 1][0] : 0);
  suffix_y[i][1] = pts[i].second * (-2 * i) + (i + 1 < N ? suffix_y[i + 1][1] : 0); 
  suffix_y[i][2] = pts[i].second            + (i + 1 < N ? suffix_y[i + 1][2] : 0);    
 } 
 double ans = 0, den = 0; 
 for(int i = 0; i + 1 < N; i++) { 
  ans += pts[i].first   * (suffix_y[i + 1][0] + suffix_y[i + 1][1] + 2 * i * suffix_y[i + 1][2]) - 
         pts[i].second * (suffix_x[i + 1][0] + suffix_x[i + 1][1] + 2 * i * suffix_x[i + 1][2]); 
 }
 for(int i = 0; i < N; i++) { 
  den += pts[i].first * pts[(i + 1) % N].second - pts[i].second * pts[(i + 1) % N].first; 
 }
 cout << fixed << setprecision(10) << ans / den << '\n'; 
 return 0; 
}