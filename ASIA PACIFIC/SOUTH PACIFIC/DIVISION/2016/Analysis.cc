#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, K;
  cin >> N >> K;
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  int ret = 1, cap = K; 
  for(int i = 0; i < N; i++) { 
    if(a[i] <= cap) { 
      cap = cap - a[i]; 
    }
    else { 
      cap = K;
      cap = cap - a[i];  
      ret++; 
    }
  }
  cout << ret << '\n'; 
  return 0; 
}