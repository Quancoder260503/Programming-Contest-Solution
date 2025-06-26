#include "bits/stdc++.h"

using namespace std;

void solve() { 
 int N; 
 cin >> N;
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 if(N == 1) { 
  cout << 1 << '\n'; 
  return; 
 }
 set<int64_t>ms; 
 for(int i = 0; i < N; i++) { 
  for(int j = i + 1; j < N; j++) { 
   int dist = a[j] - a[i]; 
   for(int x = 1; x * x <= dist; x++) { 
    if(dist % x == 0) { 
     int y = dist / x;
     if(abs(x - y) % 2 == 0) { 
      int64_t p = (x + y) / 2, q = abs(x - y) / 2;
      if((1LL * p * p - a[j] == 1LL * q * q - a[i]) && 1LL * p * p >= a[j]) { 
        ms.insert(1LL * p * p - a[j]); 
      }  
     }
    }
   }
  }
 }
 int ans = 0; 
 for(auto &x : ms) { 
  int square = 0; 
  for(int i = 0; i < N; i++) { 
   int64_t cand = a[i] + x; 
   int sqrt_cand = int(sqrt(cand)); 
   if(1LL * sqrt_cand * sqrt_cand == cand) { 
    square++; 
   }
  }
  ans = max(ans, square); 
  //cout << ans << " " << x << '\n'; 
 }
 cout << max(ans, 1) << '\n'; 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { solve(); }
  return 0; 
}
