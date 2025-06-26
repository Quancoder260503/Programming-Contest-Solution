#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Q, N;
  cin >> Q; 
  for(int iter = 0; iter < Q; iter++) { 
    cin >> N; 
    N = 3 * N; 
    vector<int>a(N);
    for(int i = 0; i < N; i++) { 
      cin >> a[i]; 
    } 
    sort(a.begin(), a.end());
    int64_t ret = 0;
    for(int i = N - 2, ctr = 0; ctr < N / 3; ctr++, i -= 2) { 
      ret += a[i]; 
    }
    cout << ret << '\n'; 
  } 
  return 0; 
}

