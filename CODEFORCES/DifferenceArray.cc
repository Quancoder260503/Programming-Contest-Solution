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
  vector<int>a(n); 
  for(auto &x : a) { 
   cin >> x; 
  }
  for(int i = 0; i < n - 1; i++) { 
   vector<int>b; 
   int pos = upper_bound(a.begin(), a.end(), 0) - a.begin(); 
   pos = max(pos - 1, 0); 
   while(sz(a) > pos) { 
    b.push_back(a.back()); 
    a.pop_back(); 
   }
   for(int i = 0; i + 1 < sz(b); i++) { 
    b[i] = b[i] - b[i + 1]; 
   }
   b.pop_back();
   sort(b.begin(), b.end()); 
   for(auto &x : b) { 
    a.push_back(x); 
   }
   //cout << pos << " " << sz(a) << '\n'; 
  }
  cout << a[0] << '\n'; 
 }
 return 0; 
}