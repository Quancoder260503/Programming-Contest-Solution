#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 for(cin >> T; T--; ) { 
  int n; 
  cin >> n; 
  double ret = 0; 
  vector<double>x(n); 
  for(int i = 0; i < n; i++) { 
   cin >> x[i]; 
  }
  for(int i = 1; i < n; i++) { 
   ret += (x[i] - x[i - 1]) * i * (n - i); 
  }
  ret = ret / 2; 
  cout << fixed << setprecision(6) << ret << '\n'; 
 }
 return 0; 
}
