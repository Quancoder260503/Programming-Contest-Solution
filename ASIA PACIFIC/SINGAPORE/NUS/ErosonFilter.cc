#include "bits/stdc++.h"

using namespace std;

const int maxn = 3e5 + 10;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0); 
  int n; 
  cin >> n; 
  cout << fixed << setprecision(10); 
  vector<double>a(n), ans(n); 
  for(auto &x : a) { 
   cin >> x; 
  } 
  double sum = 0; 
  for(int i = 0; i < n; i++) { 
   sum = sum / 2; 
   sum += a[i]; 
   ans[i] += sum; 
  }
  sum = 0; 
  for(int i = n - 1; i >= 0; i--) {  
   ans[i] += sum; 
   sum += a[i]; 
   sum = sum / 2; 
  }
  for(int i = 0; i < n; i++) { 
    cout << ans[i] << " "; 
  }
  cout << '\n'; 
  return 0; 
}