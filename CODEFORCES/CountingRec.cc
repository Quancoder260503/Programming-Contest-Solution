#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M;
  cin >> N >> M; 
  cout << 1LL * N * (N - 1) * M * (M - 1) / 4; 
  return 0; 
}