#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, D, T;
  for(cin >> T; T--; ) { 
    cin >> N >> D;
    vector<int>a(N); 
    for(int i = 0; i < N; i++) { 
      cin >> a[i]; 
    } 
    for(int j = D; j > 0; j--) { 
      for(int i = 1; i < N; i++) { 
        if(a[i] > 0) { 
          a[i - 1] += 1; 
          a[i] -= 1; 
          break; 
        }
      }
    }
    cout << a[0] << '\n'; 
  }
  return 0; 
}