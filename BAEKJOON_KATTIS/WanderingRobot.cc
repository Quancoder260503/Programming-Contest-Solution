#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 10; 
const double eps = 1e-6;

double fact[maxf], pw2[maxf]; 

void init() { 
 fact[0] = pw2[0] = 0; 
 for(int i = 1; i < maxf; i++) { 
  fact[i] = fact[i - 1] + log10(i); 
  pw2[i]  = log10(2) + pw2[i - 1]; 
 }
 return; 
}

void solve(int c) { 
 int W, H, L, U, R, D; 
 cin >> W >> H >> L >> U >> R >> D;
 double ret = 0;
 if(D < H) { 
  for(int col = 1; col < L; col++) { 
   double num = fact[D + col - 2] - fact[D - 1] - fact[col - 1]; 
   double den = D < H ? pw2[D + col - 1] : pw2[D + col - 2]; 
   ret += pow(10, num - den); 
  // cout << pow(10, num) << " " << pow(10, den) << '\n'; 
  }
 } 
 if(R < W) { 
  for(int row = 1; row < U; row++) { 
   double num = fact[R + row - 2] - fact[R - 1] - fact[row - 1]; 
   double den = R < W ? pw2[R + row - 1] : pw2[R + row - 2]; 
   ret += pow(10, num - den); 
  }
 } 
 //ret = ret > 1. + eps ? 0. : ret; 
 printf("Case #%d: %.16f\n", c + 1, ret); 
 return;  
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  init(); 
  int T;
  cin >> T;  
  for(int j = 0; j < T; j++) { solve(j); }
  return 0; 
}