#include "bits/stdc++.h"

using namespace std;

const double EPS = 1e-10;
const int maxf = 50; 

double Comb[maxf][maxf]; 

vector<double> Gauss(vector<vector<double> >& M) {
  int rows = M.size(), cols = M[0].size();
  int rank = 0;
  for (int piv = 0; piv < cols - 1 && rank < rows; piv++) {
    for (int i = rank; i < rows; i++)
      if (abs(M[i][piv]) >= EPS) {
        M[rank].swap(M[i]);
        break;
      }
    if (abs(M[rank][piv]) < EPS) continue;

    double divide_me = M[rank][piv];
    for (int j = rank; j < cols; j++) M[rank][j] /= divide_me;

    for (int i = 0; i < rows; i++) {
      if (abs(M[i][piv]) < EPS || i == rank) continue;
      double multiplier = M[i][piv] / M[rank][piv];
      for (int j = rank; j < cols; j++) M[i][j] -= multiplier * M[rank][j];
    }
    rank++;
  }

  vector<double> ans(cols - 1, -1);
  for (int i = 0; i < rank; i++) {
    int first = 0, last = cols - 2;
    for (; first < cols; first++)
      if (abs(M[i][first]) >= EPS) break;
    for (; last >= 0; last--)
      if (abs(M[i][last]) >= EPS) break;
    if (first != last) continue;  // Undetermined
    ans[first] = M[i][cols - 1];
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, C, T;
  cin >> T; 
  Comb[0][0] = 1; 
  for(int i = 1; i < maxf; i++) {
    for(int j = 0; j <= i; j++) { 
      Comb[i][j] = Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0); 
    }
  }
  cout << fixed << setprecision(10); 
  for(int iter = 0; iter < T; iter++) { 
    cin >> C >> N; 
    vector<vector<double>>mat(C + 1, vector<double>(C + 2, 0));
    for(int knownCards = 0; knownCards <= C; knownCards++) { 
      mat[knownCards][knownCards] = 1.; 
      for(int extraCards = 1; extraCards + knownCards <= C && extraCards <= N; extraCards++) { 
        mat[knownCards][extraCards + knownCards] -= Comb[knownCards][N - extraCards] * 
                                                    Comb[C - knownCards][extraCards]  / Comb[C][N]; 
      }
      if(knownCards < C) { 
        mat[knownCards][C + 1] = 1.; 
        double den = Comb[knownCards][N] / Comb[C][N]; 
        if(den == 1.) continue; 
        mat[knownCards][knownCards] = 1. - den; 
      }
    }
    vector<double>ret = Gauss(mat); 
    cout << "Case #"  << iter + 1 << ": " << ret[0] << '\n'; 
  }
  return 0;
}



/*
 Given C cards, each packages contain N distinct cards
 E(x) = {expected number booster packs needed to buy to reach full cards when we currenly have x cards}
 E(x) = 1 + E(x + 1) * P(1) + E(x + 2) * P(2) + .... + E(c) * P(c - x) 
 P(extraCards) = C(knownCards, n - extraCards) * C(c - knownCards, extraCards) / C(c, n) 

*/