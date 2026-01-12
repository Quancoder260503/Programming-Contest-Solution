#include "bits/stdc++.h"

using namespace std; 

void solve() { 
 int n, m; 
 cin >> n >> m; 
 vector<int>a(n); 
 for(int &x : a) cin >> x; 
 auto b = a;
 sort(b.begin(), b.end()); 
 int ans = 0; 
 for(int i = 0; i < n && b[i] <= m; i++) { 
   ans++; 
   m -= b[i]; 
 }
 if(ans < n && ans > 0 && m + b[ans - 1] >= a[ans]) ans++;
 cout << n - ans + 1 << '\n'; 
 return;
}

int main(void) {
  int T; 
  for(cin >> T; T--; ) solve(); 
  return 0; 
}