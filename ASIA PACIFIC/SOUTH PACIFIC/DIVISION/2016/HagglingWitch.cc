#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e7; 

unordered_map<int, double>dyn[82][82]; 

double memo(int L, int R, int T) { 
  if(T == 0) return 0; 
  if(T < 100 || L > R) return -oo; 
  if(dyn[L][R].count(T)) return dyn[L][R][T]; 
  double ret = 0; 
  for(int i = L; i <= R; i++) { 
    double curr = 0.0; 
    curr = max(curr, curr + 1.0 * (i - L) / (R - L + 1) * memo(L, i - 1, T - 100));
    double cc = memo(i, R, T - 200); 
    if(cc != -oo) curr = max(curr, curr + 1.0 * (R - i + 1) / (R - L + 1) * max(1.0 * i, cc));
    else curr = max(curr, curr + 1.0 * (R - i + 1) / (R - L + 1) * i);  
    ret = max(curr, ret);  
  }
  return dyn[L][R][T] = ret; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int L, R, T; 
  cin >> L >> R >> T; 
  cout << fixed << setprecision(10) << memo(L, R, T) << '\n'; 
  return 0; 
}