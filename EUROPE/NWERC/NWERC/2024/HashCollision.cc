#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long


int main(void) {
 int N; 
 cin >> N; 
 auto ask = [&](int cc, int rr) { 
  cout << "?" << " " << cc << " " << rr << '\n'; 
  int ret; 
  cin >> ret; 
  return ret; 
 }; 
 int f = ask(N, 1); 
 if(f == N) { 
  cout << "!" << " " << N << " " << 1 << '\n'; 
  return 0; 
 }
 int r = ask(N - f, 1); 
 cout << "!" << " " << f << " " << r << '\n'; 
 return 0; 
}