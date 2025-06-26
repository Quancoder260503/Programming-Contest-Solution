#include "bits/stdc++.h"

using namespace std;

int N, K, M;
vector<int> b;
vector<vector<int>> p, q;
vector<vector<double>> dyn;

double memo(int pos, int mask, int intervention) {
  if (pos == N) return (mask & 1);
  double &ret = dyn[mask][intervention];
  if (ret >= 0) return ret;
  ret = 0; 
  if(pos > 0) { 
    for(int i = pos; i < N; i++) { 
       b[i] += (mask & 1 ? p[pos - 1][i - pos] : q[pos - 1][i - pos]); 
    }
  }
  if(b[pos] <= -M) { 
    ret = memo(pos + 1, 2 * mask, intervention); 
  }
  else if(b[pos] >= 0) { 
    ret = memo(pos + 1, 2 * mask + 1, intervention); 
  }
  else { 
    double Prob_positive = memo(pos + 1, 2 * mask + 1, intervention); 
    double Prob_negative = memo(pos + 1, 2 * mask    , intervention); 
    ret   = (Prob_negative * (-b[pos]) + 
             Prob_positive * (M + b[pos])) / M; 
    if(intervention > 0) { 
      Prob_negative = memo(pos + 1, 2 * mask, intervention - 1); 
      Prob_positive = memo(pos + 1, 2 * mask + 1, intervention - 1); 
      double Dice_neg = 1.0 * (b[pos] * b[pos]) / (M * M); 
      double Dice_pos = 1.0 * (M + b[pos]) * (M + b[pos]) / (M * M);
      ret = max(ret, Prob_negative * Dice_neg + Prob_positive * (1.0 - Dice_neg)); 
      ret = max(ret, Prob_negative * (1.0 - Dice_pos) + Prob_positive * Dice_pos); 
    }
  }
  if(pos > 0) { 
    for(int i = pos; i < N; i++) { 
       b[i] -= (mask & 1 ? p[pos - 1][i - pos] : q[pos - 1][i - pos]); 
    }
  }
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> K >> M;
  b.resize(N);
  q.resize(N);
  p.resize(N);
  dyn.resize((1 << N), vector<double>(K + 1, -1));
  for (int i = 0; i < N; i++) {
    cin >> b[i];
    p[i].resize(N - i - 1);
    q[i].resize(N - i - 1);
    for (int j = 0; j < N - i - 1; j++) {
      cin >> p[i][j];
    }
    for (int j = 0; j < N - i - 1; j++) {
      cin >> q[i][j];
    }
  }
  cout << fixed << setprecision(6) << memo(0, 1, K) << '\n';
  return 0;
}


/* 
   dyn[event][mask][intevention] = {maximum probability}

*/