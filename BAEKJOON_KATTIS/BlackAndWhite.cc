#include "bits/stdc++.h"

using namespace std; 

const int LOG = 21; 

double dp[1 << LOG], Prob[LOG];
int N; 

double f(int mask) { 
  if(__builtin_popcount(mask) == 2) return 0; 
  double &ret = dp[mask]; 
  if(ret != -1) return ret;
  ret = 1; 
  double totalProbUp = 1.;
  double totalProbDown = 1.; 
  for(int i = 0; i < N; i++) { 
    if(mask & (1 << i)) { 
      totalProbUp *= Prob[i]; 
      totalProbDown *= (1. - Prob[i]); 
    } 
  } 
  double nextProb = 0.; 
  for(int i = 0; i < N; i++) { 
    if(mask & (1 << i)) {
      nextProb += totalProbUp / Prob[i] * (1. - Prob[i]); 
      nextProb += totalProbDown / (1. - Prob[i]) * Prob[i]; 
      ret += f(mask ^ (1 << i)) * (totalProbUp / Prob[i] * (1. - Prob[i]) + 
                                   totalProbDown / (1. - Prob[i]) * Prob[i]);  
    }
  }
  if(nextProb > 0) ret = ret / nextProb; 
  return ret;  
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  for(int i = 0; i < (1 << LOG); i++) { 
    dp[i] = -1; 
  }
  cin >> N;
  for(int i = 0; i < N; i++) { 
    cin >> Prob[i]; 
  }
  cout << fixed << setprecision(10) << f((1 << N) - 1) << '\n'; 
  return 0; 
}