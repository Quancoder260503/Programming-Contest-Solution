#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())
#define int64_t long long

using type = int64_t; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, T; 
 for(cin >> T; T--; ) { 
  cin >> n; 
  vector<int>a(n), b(n), pos(n); 
  for(auto &x : a) { 
   cin >> x; 
   --x; 
  }
  for(auto &x : b) { 
   cin >> x; 
   --x; 
  }
  for(int i = 0; i < n; i++) { 
   pos[a[i]] = i; 
  }
  int ptr = n - 1, ret = 1; 
  while(ptr > 0 && pos[b[ptr]] > pos[b[ptr - 1]]) { 
   ret++; 
   ptr--; 
  }
  cout << n - ret << '\n'; 
 }
 return 0; 
} 
