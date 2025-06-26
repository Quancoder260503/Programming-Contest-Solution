#include "bits/stdc++.h"

using namespace std;

const double EPS = 1e-10;

#define double long double

vector<double> Gauss(vector<vector<double> >& M){
  int rows = M.size(), cols = M[0].size();
  int rank = 0;
  for(int piv=0;piv<cols-1 && rank<rows;piv++){
    for(int i=rank;i<rows;i++)
      if(abs(M[i][piv]) >= EPS){
        M[rank].swap(M[i]);
        break;
      }
    if(abs(M[rank][piv]) < EPS) continue;

    double divide_me = M[rank][piv];
    for(int j=rank;j<cols;j++) M[rank][j] /= divide_me;

    for(int i=0;i<rows;i++){
      if(abs(M[i][piv]) < EPS || i == rank) continue;
      double multiplier = M[i][piv] / M[rank][piv];
      for(int j=rank;j<cols;j++)
        M[i][j] -= multiplier * M[rank][j];
    }
    rank++;
  }

  vector<double> ans(cols-1,-1);
  for(int i=0;i<rank;i++){
    int first = 0, last = cols-2;
    for(;first<cols;first++) if(abs(M[i][first]) >= EPS) break;
    for(;last>=0;last--)     if(abs(M[i][last ]) >= EPS) break;
    if(first != last) continue; // Undetermined
    ans[first] = M[i][cols-1];
  }

  return ans;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int tc, ProbNum, N, P;
    double left, right;  
    cin >> tc; 
    while(tc--) { 
        cin >> ProbNum >> N >> P >> left >> right; 
        vector<vector<double>>mat(N + 1, vector<double>(N + 1)); 
        for(int i = 0; i < N; i++) { 
            mat[i][i] = mat[N][i] = 1.0; 
            mat[i][(i + 1) % N]     = -right; 
            mat[i][(i - 1 + N) % N] = -left; 
        }
        mat[N][N] = 1.0; 
        mat[0][N] = 1.0 - left - right; 
        vector<double>ret = Gauss(mat); 
        cout << ProbNum << " " << fixed << setprecision(2) << ret[P] * 100.0 << '\n'; 
    }
    return 0; 
}