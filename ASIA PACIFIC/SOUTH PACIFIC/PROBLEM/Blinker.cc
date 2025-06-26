#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0);
  cout.tie(0);
  int64_t N;
  cin >> N; 
  int64_t ret = 1; 
  for(int i = 2; 1LL * i * i <= N; i++) { 
    if(N % i == 0) { 
      int amt = 0; 
      while(N % i == 0) { 
        N = N / i; 
        amt++; 
      } 
      ret = ret * (amt + 1); 
    }
  }
  if(N > 1) ret = ret * 2; 
  cout << ret - 1 << '\n'; 
  return 0; 
} 