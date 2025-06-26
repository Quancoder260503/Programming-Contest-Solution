#include "bits/stdc++.h"

using namespace std;

const double eps = 1e-12;

int main(void) { 
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int N, T; 
  cin >> N >> T; 
  vector<array<double, 3>>subject(N);
  for(int i = 0; i < N; i++) { 
    cin >> subject[i][0] >> subject[i][1] >> subject[i][2]; 
  } 
  auto F = [&](double x) {
    double ret = 0; 
    for(int i = 0; i < N; i++) { 
      ret += max(0.0, (x - subject[i][1]) / (2.0 * subject[i][0])); 
    } 
    return ret <= T; 
  };
  double lo = -1e3, hi = 1e3; 
  for(; lo + eps < hi;) {
    double mid = (lo + hi) / 2;
    if(!F(mid)) lo = mid; 
    else        hi = mid; 
  }
  double ret = 0; 
  for(int i = 0; i < N; i++) { 
    double c = max(0.0, (lo - subject[i][1]) / (2.0 * subject[i][0])); 
    ret += subject[i][0] * c * c + subject[i][1] * c + subject[i][2]; 
  }
  cout << fixed << setprecision(10) << ret / N << '\n'; 
  return 0; 
}