#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())
#define double long double
 
const int maxn = 1e6 + 10; 
 
vector<int>g[maxn]; 
int n, a[maxn]; 
 
int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> n; 
  for(int i = 0; i < n; i++) { 
   cin >> a[i]; 
   g[a[i]].push_back(i); 
  }
  double ret = 0; 
  for(int i = 0; i < maxn; i++) { 
   for(int j = 0; j < sz(g[i]); j++) { 
    double left = g[i][j] - (j ? g[i][j - 1] : -1.0);
    double right =  (n - g[i][j]); 
    ret += (2.0 * left * right - 1.0) / (1.0 * n * n); 
   }
  }
  //ret = ret / (n * n); 
  cout << fixed << setprecision(7) << ret << '\n'; 
  return 0; 
}