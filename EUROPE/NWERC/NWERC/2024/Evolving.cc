#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
 int64_t res = 1;
 while (b > 0) {
  if (b & 1) res = (res * a) % p;
  a = (a * a) % p;
  b >>= 1;
 }
 return res;
}

int main(void) {
 int N;  
 int64_t K; 
 string S; 
 cin >> N >> K >> S; 
 int64_t d = mod_pow(2, K, N); 
 for(int i = 0; i < N; i++) { 
  cout << S[i * d % N]; 
 }
 cout << '\n';
 return 0; 
}