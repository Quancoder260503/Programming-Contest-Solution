#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M; 
 cin >> N >> M; 
 vector<int>a(N), b(M), ord(N);
 iota(ord.begin(), ord.end(), 0);  
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 sort(ord.begin(), ord.end(), [&](int i, int j) { 
  return a[i] > a[j]; 
 }); 
 for(int i = 0; i < M; i++) { 
  cin >> b[i]; 
 }
 vector<vector<int>>ret(M); 
 vector<int64_t>denom(M); 
 for(int i = 0; i < sz(ord); i++) { 
  int x = ord[i], opt = 0; 
  for(int j = 0; j < M; j++) { 
   if(1. * b[opt] * a[x] * (a[x] + denom[j]) < 1. * b[j] * a[x] * (a[x] + denom[opt])) { 
    opt = j;  
   }
  }
  denom[opt] += a[x]; 
  ret[opt].push_back(x); 
 }
 for(int i = 0; i < M; i++) { 
  cout << sz(ret[i]) << " "; 
  for(auto x : ret[i]) { 
   cout << x + 1 << " "; 
  }
  cout << '\n'; 
 }
 return 0; 
}