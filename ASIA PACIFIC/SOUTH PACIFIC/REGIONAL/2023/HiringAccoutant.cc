#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 10; 
const double oo = 1e20; 


int N, M[maxf], S[maxf];
double dyn[maxf], Prob[maxf];

int main(void) { 
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  cout.tie(0); 
  cin >> N; 
  for(int i = 1; i <= N; i++) { 
    cin >> S[i]; 
  } 
  for(int i = 1; i <= N; i++) { 
    cin >> Prob[i]; 
  }
  for(int i = 1; i <= N; i++) { 
    cin >> M[i]; 
  }
  for(int i = 0; i < maxf; i++) { 
    dyn[i] = -oo; 
  }
  double ret = -oo; 
  for(int i = N; i > 0; i--) { 
    dyn[i] = max(dyn[i + 1], Prob[i] * S[i] + 
                             max(0.0, (1. - Prob[i]) * dyn[i + M[i] + 1])); 
    ret = max(ret, dyn[i]); 
  }
  cout << fixed << setprecision(10) << ret << '\n'; 
  return 0; 
}