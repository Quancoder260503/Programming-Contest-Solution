#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0);
  cout.tie(0); 
  int N, T; 
  cin >> N >> T;
  int sum = 0; 
  for(int i = 1; i <= T; i++) {
    string s = to_string(i); 
    sum += sz(s); 
    if(2 * (sz(s) + 1) <= N) { 
      if(1LL * N * i - (sum + 2 * i + 1LL * sz(s) * i) >= T) { 
        cout << i << '\n'; 
        exit(0); 
      }
    }
    else break; 
  }
  cout << -1 << '\n'; 
  return 0; 
}