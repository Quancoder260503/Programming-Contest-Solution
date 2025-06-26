#include "bits/stdc++.h"

using namespace std;

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res * tmp;
    }
    tmp = (int64_t)tmp * tmp;
    k >>= 1;
  }
  return res;
}

int64_t f(int64_t p, int64_t k, int64_t x) { 
  if(k <= 0) return 1; 
  if(p == 2) { 
    if(k == 1) return 2;  
    int64_t u = fpow(p, k - 2) / gcd(x, fpow(p, k - 2)); 
    if(x & 1) u = u * 2; 
    return u + f(p, k - x, x); 
  }
  int64_t u = (fpow(p, k) - fpow(p, k - 1)) / gcd(x, (fpow(p, k) - fpow(p, k - 1)));
  return u + f(p, k - x, x);  
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int64_t P, Q, N;
  cin >> P >> Q >> N;
  int64_t ret = 1; 
  for(int64_t i = 2; i * i <= N; i++) { 
    if(N % i == 0) { 
      int ctr = 0; 
      while(N % i == 0) {ctr++; N = N / i; }
      ret = ret * f(i, ctr, P);   
    }
  } 
  if(N > 1) { ret = ret * f(N, 1, P); }
  cout << ret << '\n'; 
  return 0; 
}