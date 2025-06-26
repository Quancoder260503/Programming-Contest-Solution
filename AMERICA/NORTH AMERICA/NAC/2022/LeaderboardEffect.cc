#include "bits/stdc++.h"

using namespace std;

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, T; 
 cin >> N >> T; 
 vector<int>r(N), c(N);
 vector<double>Prob(N); 
 for(int i = 0; i < N; i++) { 
  cin >> r[i] >> c[i] >> Prob[i]; 
 }   
 vector<vector<double>>probSolve(N, vector<double>(T + 1)); 
 vector<vector<double>>dp(T + 1, vector<double>(1 << N, 0.));  
 dp[0][0] = 1.; 
 for(int curr_time = 0; curr_time <= T; curr_time++) { 
  for(int i = 0; i < N && curr_time > 0; i++) {
   probSolve[i][curr_time] += probSolve[i][curr_time - 1]; 
  }
  for(int mask = 0; mask < (1 << N); mask++) { 
   if(dp[curr_time][mask] == 0.) continue; 
   double notRead = 0, den = 0; 
   for(int i = 0; i < N; i++) { 
    if(mask & (1 << i)) continue; 
    notRead++; 
    den += probSolve[i][curr_time];
   }
   for(int i = 0; i < N; i++) { 
    if(mask & (1 << i)) continue; 
    double probRead = (den == 0. ? 1. / notRead : probSolve[i][curr_time] / den); 
    if(curr_time + r[i] + c[i] <= T) { 
     dp[curr_time + r[i] + c[i]][mask | (1 << i)] += Prob[i] * probRead * dp[curr_time][mask]; 
     probSolve[i][curr_time + r[i] + c[i]] += Prob[i] * probRead * dp[curr_time][mask]; 
    } 
    if(curr_time + r[i] <= T) { 
     dp[curr_time + r[i]][mask | (1 << i)] += (1. - Prob[i]) * probRead * dp[curr_time][mask];
    }
   }
  }
 }
 cout << fixed << setprecision(10); 
 for(int i = 0; i < N; i++) { 
  cout << probSolve[i][T] << '\n'; 
 }
 return 0; 
}
/* 
 * Let f(i, m) be the expected number of teams that solve problem i in the contest given that there are m teams
 * The problem requires us to compute f(i, m) / m when m grows to oo, 
 * However note that f(i, m) = m * P(i) where P(i) is the probability that a team solve the problem in the contest
 * --> f(i, m) / m = P(i)
 * Observe the case in the start of the contest, given m teams participation then let 
  X be the number of teams that will read the problem and 
  Y be the number of team that solve the problem given that they read it 
  (X, Y) have binominal distribution so the E(Y) = n * p where n is the number of team that read the problem, p is the probability 
  that the team will solve the problem 
  E(teams that solve problem at t + r[i] + c[i]) += n * Prob[i] * P(A team read the problem at time t) where n is the number of team participates in the contest 
  E(teams that solve problem at t + r[i] + c[i]) / n += Prob[i] * P(A team read the problem at time t)
  -> Prob(A team solve the problem at t + r[i] + c[i]) depends on Prob(A team read the problem at time t)
  The problem now boiled downs to compute the probability that a problem will be chosen to read, let this be g(i)
  In the case in the beginning the contest, 
  g[i] = 1 / N for all i 
  Otherwise, 
  Since the number of team approaches oo we use Expected value of teams that solve the problem to estimate the 
  probability that the problem will be chosen. 
  E(i) / Sum(E) ~ P(i) / Sum(P)

 */