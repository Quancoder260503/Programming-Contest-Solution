#include "bits/stdc++.h"
 
using namespace std;
 
#define double long double
 
const int maxf = 102;
 
double Prob[maxf][maxf][maxf];
 
int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int R, P, S;
  cin >> R >> S >> P;
  Prob[R][P][S] = 1.0;
  for (int rock = R; rock >= 0; rock--) {
    for (int paper = P; paper >= 0; paper--) {
      for (int scissor = S; scissor >= 0; scissor--) {
        double den = 1.0 * rock * paper + 1.0 * rock * scissor + 1.0 * paper * scissor; 
        if(den == 0) continue; 
        if(rock > 0) {
          Prob[rock - 1][paper][scissor] += 1.0 * rock * paper * Prob[rock][paper][scissor]   / den;  
        }
        if(paper > 0) { 
          Prob[rock][paper - 1][scissor] += 1.0 * scissor * paper * Prob[rock][paper][scissor] / den;  
        }
        if(scissor > 0) { 
          Prob[rock][paper][scissor - 1] += 1.0 * rock * scissor * Prob[rock][paper][scissor]  / den;  
        }
      }
    }
  }
  vector<double> ret(3);
  for (int i = 1; i <= R; i++) {
    ret[0] += Prob[i][0][0];
  }
  for (int i = 1; i <= P; i++) {
    ret[1] += Prob[0][i][0];
  }
  for (int i = 1; i <= S; i++) {
    ret[2] += Prob[0][0][i];
  }
  cout << fixed << setprecision(12) << ret[0] << " " << ret[2] << " " << ret[1]
       << '\n';
  return 0;
}