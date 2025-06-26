#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<int>a(N), b(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  for(int i = 0; i < N; i++) { 
   cin >> b[i]; 
  }
  vector<array<int64_t, 3>>stk; 
  for(int i = 0; i < N; i++) { 
   int64_t num = 1LL * a[i] * b[i], den = 1LL * b[i] * b[i], elem = 1; 
   while(sz(stk) && 1LL * stk.back()[0] * den < 1LL * stk.back()[1] * num) {
    num  += stk.back()[0]; 
    den  += stk.back()[1];
    elem += stk.back()[2]; 
    stk.pop_back(); 
   }
   stk.push_back({num, den, elem});
  }
  int pos = N - 1; 
  double ret = 0.; 
  while(sz(stk)) { 
   auto [num, den, elem] = stk.back(); 
   stk.pop_back(); 
   double r = 1. * num / den; 
   for(int j = pos; j > pos - elem; j--) {
    ret += 1. * (1. * a[j] - r * b[j]) * (1. * a[j] - r * b[j]);   
   }
   pos = pos - elem; 
  }
  cout << fixed << setprecision(10) << ret << '\n'; 
  return 0;
}