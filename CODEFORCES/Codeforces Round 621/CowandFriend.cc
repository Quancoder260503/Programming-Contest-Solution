#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, T, X; 
  for(cin >> T; T--; ) { 
    cin >> N >> X;
    set<int>s; 
    for(int i = 0, c; i < N; i++) { 
      cin >> c; 
      s.insert(c); 
    } 
    if(s.count(X)) { 
      cout << 1 << '\n'; 
    }
    else {
      cout << max(2, (int) ceil(1. * X / *prev(s.end()))) << '\n'; 
    }
  }
  return 0; 
}