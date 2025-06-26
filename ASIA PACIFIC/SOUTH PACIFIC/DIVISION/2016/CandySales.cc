#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e7; 

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
  int ret = oo, min_so_far = oo;
  for(int i = 0; i < N; i++) { 
    cout << min(min_so_far + i, a[i]) << " "; 
    min_so_far = min(min_so_far, a[i] - i); 
  }
  return 0; 
}
