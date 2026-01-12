#include "bits/stdc++.h"

using namespace std; 

#define ll long long 

void solve() { 
 int n, m; 
 cin >> n >> m; 
 vector<int>a(n); 
 for(auto &x : a) cin >> x; 
 int mid = n >> 1;
 ll ans = 0; 
 for(int i = 0; i < mid; i += m) { 
  ans +=  a[i] - a[mid];  
 }
 for(int i = n - 1; i > mid; i -= m) { 
  ans += a[mid] - a[i]; 
 }
 ans = ans * 2; 
 cout << -ans << '\n'; 
 return;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T;
  for(T = 1; T--; ) solve(); 
  return 0; 
}