#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N; 
  cin >> N; 
  for(int c = 0; c <= N; c += 2) { 
   if((N - c) % 3 == 0) { 
    int d = (N - c) / 3; 
    c = c / 2; 
    cout << c + d << '\n'; 
    for(int j = 0; j < d; j++) cout << 3 << " ";
    for(int j = 0; j < c; j++) cout << 2 << " "; 
    break; 
   }
  }
  return 0; 
}