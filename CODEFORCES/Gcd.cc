#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 int64_t ans = LLONG_MAX; 
 vector<int>primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}; 
 for(int mask = 0; mask < (1 << sz(primes)); mask++) { 
  int64_t g = 1; 
  for(int j = 0; j < sz(primes); j++) { 
   if(mask >> j & 1) { 
    g = g * primes[j]; 
   }
  }
  int64_t c = 1; 
  for(int i = 0; i < N; i++) { 
   c = c & (gcd(g, a[i]) > 1);
  }
  if(c) { 
   ans = min(ans, g); 
  } 
 }
 cout << ans << '\n'; 
 return 0;
}