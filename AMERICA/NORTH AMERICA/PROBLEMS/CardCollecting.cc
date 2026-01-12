#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define double long double

const double oo = 1e8; 
const int maxn = 103;

double prob[12][12][maxn], dp[maxn][maxn * maxn];  

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cout << fixed << setprecision(10); 
 int N, S, D, K, T; 
 for(cin >> T; T--; ) {
  cin >> N >> S >> K >> D; 
  vector<double>p(N + 1); 
  for(int i = 0; i <= N; i++) { 
   cin >> p[i];  
  }
  for(int i = 0; i < 12; i++) { 
   for(int j = 0; j < 12; j++) { 
    for(int k = 0; k < maxn; k++) { 
     prob[i][j][k] = -1.; 
    }
   }
  }
  function<double(int, int, int)> Prob = [&](int new_cards, int new_unique, int current_unique) -> double { 
   if(new_cards == 0) return new_unique == 0; 
   if(prob[new_cards][new_unique][current_unique] != -1) return prob[new_cards][new_unique][current_unique]; 
   double &ret = prob[new_cards][new_unique][current_unique]; 
   if(ret != -1) return ret;
   double currProb = 1. * current_unique / N; 
   ret = currProb       * Prob(new_cards - 1, new_unique, current_unique) + 
         (1 - currProb) * Prob(new_cards - 1, new_unique - 1, current_unique + 1); 
   return ret; 
  }; 
  for(int i = 0; i < maxn; i++) { 
   for(int j = 0; j < maxn * maxn; j++) { 
    dp[i][j] = -1;
   }
  }
  function<double(int, int)> memo = [&](int unique_cards, int duplicated) -> double { 
   if(unique_cards >= N || duplicated >= N * D) return 0.; 
   double &ret = dp[unique_cards][duplicated]; 
   if(ret != -1) return ret; 
   ret = 1 / p[unique_cards];
   for(int new_cards = 0; new_cards <= K; new_cards++) {
    ret += Prob(K, new_cards, unique_cards) * memo(unique_cards + new_cards, duplicated + K - new_cards); 
   }
   if(duplicated >= D) { 
    ret = min(ret, memo(unique_cards + 1, duplicated - D));
   } 
   return ret; 
  }; 
  cout << memo(S, 0) << '\n'; 
 } 
 return 0; 
}
/*
 * Lesson : Random variable is not fixed, Try to use something fixed (e.g. Expected Value directly when not 
 conditioned on any other Random variable)
 */ 