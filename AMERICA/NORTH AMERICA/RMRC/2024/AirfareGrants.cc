#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<int>arr(N); 
  for(int i = 0; i < N; i++) { 
   cin >> arr[i]; 
  }
  sort(arr.begin(), arr.end()); 
  int reim = arr.back() / 2; 
  cout << max(0, arr[0] - reim) << '\n'; 
  return 0; 
}