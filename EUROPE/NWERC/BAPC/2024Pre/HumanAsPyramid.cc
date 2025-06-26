#include "bits/stdc++.h"
using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int64_t N; 
 cin >> N;
 int n = 1; 
 for(n = 1; n <= N; n++) { 
  if(1LL * n * (n + 1) / 2 >= N) { 
    break; 
  }
 } 
 if(1LL * n * (n + 1) / 2 != N) n--; 
 cout << n << '\n'; 
 return 0; 
}