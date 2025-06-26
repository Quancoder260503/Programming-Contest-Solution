#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, K, T; 
  cin >> N >> K >> T; 
  cout << fixed << setprecision(10); 
  vector<int>a(N);
  vector<double>Prob(N);  
  for(int i = 0; i < N; i++) { 
    cin >> Prob[i] >> a[i]; 
  }
  vector<vector<vector<double>>>dp(N + 1, vector<vector<double>>(K + 1, vector<double>(T + 1)));
  vector<int>ord(N); 
  iota(ord.begin(), ord.end(), 0); 
  sort(ord.begin(), ord.end(), [&](int x, int y) { 
    return a[x] < a[y]; 
  }); 
  vector<double>ret(N); 
  dp[0][0][0] = 1.; 
  for(int i = 0; i < sz(ord); i++) { 
    int pos = ord[i]; 
    for(int j = K - 1; j >= 0; j--) { 
      for(int k = a[pos]; k <= T; k++) { 
        double probIn = 1. * (K - j - 1) / (N - i - 1); 
        ret[pos]                     += Prob[pos] * dp[i][j][k - a[pos]]; 
        dp[i + 1][j + 1][k]          += dp[i][j][k - a[pos]] * Prob[pos] * probIn;
        dp[i + 1][j + 1][k - a[pos]] += dp[i][j][k - a[pos]] * (1. - Prob[pos]) * probIn;
        dp[i + 1][j][k - a[pos]]     += dp[i][j][k - a[pos]] * (1. - probIn);
      }
    }
  }
  for(int i = 0; i < N; i++) { 
    cout << ret[i] << '\n'; 
  }
  return 0; 
}

/* 
    dp[i][j][k] = {probability that there are j problem is solved by the team out of the first i-th problem and the current time 
                   limit is k}

    Comb(N - i, K - 1) / 2 ^ (N - i)
*/ 