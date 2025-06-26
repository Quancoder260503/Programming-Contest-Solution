#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

void doit(int64_t N, int64_t M) { 
 if(N == 0 || M == 0) { 
  cout << N << " " << M << '\n'; 
  exit(0); 
 }
 int canGo = false; 
 if(N >= 2 * M) { 
    N = N - (N / (2 * M) * (2 * M)); 
    canGo = true; 
 }
 else if(M >= 2 * N) { 
    M = M - (M / (2 * N) * (2 * N)); 
    canGo = true; 
 }
 if(canGo) doit(N, M); 
 else { 
  cout << N << " " << M << '\n'; 
  exit(0); 
 }
 return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int64_t N, M; 
  cin >> N >> M; 
  doit(N, M); 
  return 0; 
}