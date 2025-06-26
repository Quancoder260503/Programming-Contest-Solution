#include "bits/stdc++.h"

using namespace std; 

const int maxf = 1e5 + 2; 

int N, P, L[maxf], R[maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> P; 
  for(int i = 0; i < N; i++) { 
    cin >> L[i] >> R[i]; 
  } 
  double ret = 0; 
  for(int i = 0; i < N; i++) { 
    double num = 0.0;
    num += 1.0 * (R[i] / P - (L[i] - 1) / P) * (R[(i + 1) % N] - L[(i + 1) % N] + 1);
    num += 1.0 * (R[i] - L[i] + 1) * (R[(i + 1) % N] / P - (L[(i + 1) % N] - 1) / P);
    num -= 1.0 * (R[i] / P - (L[i] - 1) / P) * (R[(i + 1) % N] / P - (L[(i + 1) % N] - 1) / P);
    double den = 1.0 * (R[i] - L[i] + 1) * (R[(i + 1) % N] - L[(i + 1) % N] + 1); 
    ret += num / den;   
  }
  cout << fixed << setprecision(10) << ret * 2000 << '\n'; 
  return 0; 
}
