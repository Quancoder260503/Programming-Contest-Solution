#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

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
  int64_t ret = 0;
  for(int i = 0; i < sz(arr); i++) { 
    if(arr[i] < 0) { 
      ret = ret - arr[i];
    }
    else { 
        ret += arr[i]; 
    } 
  }
  cout << ret << '\n'; 
  return 0; 
}