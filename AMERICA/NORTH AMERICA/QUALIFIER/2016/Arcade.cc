#include "bits/stdc++.h"

using namespace std; 

#define double long double 

const double EPS = 1e-10;

double Gauss(vector<vector<double> >& M){
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
  return M[0][cols - 1]; 
  /* 
  vector<double> ans(cols-1,-1);
  for(int i=0;i<rank;i++){
    int first = 0, last = cols-2;
    for(;first<cols;first++) if(abs(M[i][first]) >= EPS) break;
    for(;last>=0;last--)     if(abs(M[i][last ]) >= EPS) break;
    if(first != last) continue; // Undetermined
    ans[first] = exp(M[i][cols-1]);
  }
  return ans; 
*/ 
}

int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    cout << fixed << setprecision(10); 
    int n; 
    cin >> n; 
    int m = n * (n + 1) / 2; 
    vector<int>a(m + 1); 
    for(int i = 1; i <= m; i++) {
        cin >> a[i]; 
    }
    vector<vector<double>>G(m + 1, vector<double>(m + 2, 0)); 
    auto To = [&](int i, int j) { 
        return i * (i + 1) / 2 + j; 
    }; 
    for(int i = 1; i <= n; i++) { 
        for(int j = 1; j <= i; j++) { 
           double p0, p1, p2, p3, p4; 
           cin >> p0 >> p1 >> p2 >> p3 >> p4;
         //  cout << i << " " << j << " " << p0 << " " << p1 << " " << p2 << " " << p3 << " " << p4 << " " << a[To(i - 1, j)] << '\n'; 
           G[To(i - 1, j)][To(i - 1, j)] += 1.0;
           if(i > 1 && j > 1)                 { G[To(i - 1, j)][To(i - 2, j - 1)]  += -p0; }
           if(i > 1)                          { G[To(i - 1, j)][To(i - 2, j)]      += -p1; }
           if(i < n)                          { G[To(i - 1, j)][To(i, j)]          += -p2; }
           if(i < n && j <= i + 1)            { G[To(i - 1, j)][To(i, j + 1)]      += -p3; }
           G[To(i - 1, j)][m + 1] += p4 * a[To(i - 1, j)]; 
        }   
    }
    cout << Gauss(G) << '\n'; 
    return 0; 
}