#include "bits/stdc++.h"

using namespace std;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);  
  int N;
  cin >> N; 
  char c = (N % 2 == 0 ? 'a' : 'b'); 
  cout << 1 << " " << 2 << " " << c << '\n'; 
  for(int i = 3; i <= N; i++) { 
    cout << c << " " << i << " " << (c == 'a' ? 'b' : 'a') << '\n'; 
    c = (c == 'a' ? 'b' : 'a'); 
  }
  return 0; 
}