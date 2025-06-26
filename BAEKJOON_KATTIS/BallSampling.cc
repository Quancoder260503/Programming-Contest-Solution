#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define double long double

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N;
  cin >> N; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  int sum = accumulate(a.begin(), a.end(), 0); 
  vector<double>dyn((1 << N), 0);
  for(int mask = (1 << N) - 1; mask >= 0; mask--) { 
    int c_sum = 0; 
    dyn[mask] = 1.0; 
    for(int i = 0; i < N; i++) { 
      if(mask & (1 << i)) continue; 
      c_sum += a[i]; 
      dyn[mask] += dyn[mask | (1 << i)] * a[i] / sum; 
    }
    if(c_sum == 0) continue; 
    dyn[mask] = dyn[mask] * sum / c_sum; 
  }
  cout << fixed << setprecision(10) << dyn[0] - 1. << '\n'; 
  return 0; 
}
/*
  dyn[mask] = {expected number of moves until we get to the state 'mask'}

*/