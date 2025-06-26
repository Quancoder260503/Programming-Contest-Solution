#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 int64_t sum = 0, opt = 0; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  sum += x; 
  opt = max(opt, 1LL * x); 
 }
 cout << min(sum / 3, sum - opt) << '\n';
 return 0; 
}