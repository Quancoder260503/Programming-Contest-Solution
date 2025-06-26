#include "bits/stdc++.h"

using namespace std; 

#define double long double

const double oo = 1e20; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, X;
  cin >> N >> X;
  double C = 1. * X / 1000000; 
  vector<vector<double>>dyn(2, vector<double>(N + 1)), Prob(2, vector<double>(N + 1)); 
  int st = 0; 
  for(int i = 0; i <= N; i++) { 
    cin >> Prob[st][i]; 
    Prob[st][i] /= 1000000; 
    dyn[st][i] = i; 
  }
  for(int num = N - 1; num >= 0; num--, st = st ^ 1) { 
    for(int w = 0; w <= num; w++) { 
      Prob[st ^ 1][w] = Prob[st][w + 1] * (w + 1) / (num + 1) + Prob[st][w] * (num + 1 - w) / (num + 1); 
      double pL = Prob[st][w + 1] * (w + 1) / (num + 1); 
      double pR = Prob[st][w] * (num + 1 - w) / (num + 1); 
      if(pL + pR == 0) continue; 
      double prob = pL / (pL + pR); 
      dyn[st ^ 1][w] = max<double>(w, prob * dyn[st][w + 1] + (1. - prob) * dyn[st][w] - C); 
    }
  }
  cout << fixed << setprecision(10) << dyn[st][0] << '\n'; 
  return 0; 
}

/*
 dyn[i][j] = {maximum expected profit given that we pulled in i red balls in the bag 
              and j blue balls }
 Prob[i][j] = {Probability that we pulled a red ball given that the bag has i red ball 
              and j blue ball}

  if we have already seen i red balls then the bag can have exactly i, i + 1, i + 2, ..., N - j red balls. 
  Let S = P(i) + P(i + 1) + P(i + 2) + ... + P(N - j). 
  Prob[i][j] = P(i) / S * (i - i) / (N - i - j) + P(i + 1) / S * (i + 1 - i) / (N - i - j) + ... + P(N - j) / S * (N - j) / (N - j - 1) 

  dyn[i][j] = max(0, Prob[i][j] * (dyn[i + 1][j] + 1.0 - c) + (1.0 - Prob[i][j]) * (dyn[i][j + 1] - c)). 

*/