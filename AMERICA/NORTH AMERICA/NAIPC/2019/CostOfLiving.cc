#include "bits/stdc++.h"

using namespace std; 

#define double long double 

/* Template copied from Darcy Best */

const double EPS = 1e-10;

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
    ans[first] = exp(M[i][cols-1]);
  }

  return ans;
}


int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);  
   // cout << fixed << setprecision(10); 
    int y, c, q; 
    cin >> y >> c >> q;
    vector<double>inflation(y, -1.0); 
    vector<vector<double>>price(y, vector<double>(c)); 
    vector<vector<double>>ret(5000, vector<double>(5000, -1.0)); 
    for(int i = 0; i < y - 1; i++) { 
        cin >> inflation[i]; 
    }
    for(int i = 0; i < y; i++) 
    for(int j = 0; j < c; j++) { 
        cin >> price[i][j]; 
    }
    vector<vector<double>>T(c * y, vector<double>(c * y + y + c + 1)); 
    for(int i = 0; i < c; i++) { 
        for(int j = 1; j < y; j++) { 
            if(inflation[j - 1] > 0) {  T[j + y * i][c * y + c + y]   += log(inflation[j - 1]);  }
            else { T[j + y * i][c * y + j - 1] -= 1.0; }
            if(price[j - 1][i] > 0) {   T[j + y * i][c * y + c + y]   += log(price[j - 1][i]); }
            else { T[j + y * i][i * y + j - 1] -= 1.0; }
            if(price[j][i] > 0) {       T[j + y * i][c * y + c + y]   -= log(price[j][i]);      }
            else { T[j + y * i][i * y + j]     += 1.0;  }
            T[j + y * i][c * y + y + i] = -1.0; 
        }
    }
    auto gaussian = Gauss(T); 
    //for(auto &x : ret) cout << x << '\n'; 
    for(int j = 0; j < gaussian.size(); j++) if(gaussian[j] > 0) {
        ret[j % y][j / y] = gaussian[j]; 
    }
    for(int i = 0; i < c; i++) {
        for(int j = 0; j < y; j++) { 
            if(price[j][i] > 0) { 
                ret[j][i] = price[j][i]; 
            }
        }
    }
    for(int i = 0, a, b; i < q; i++) { 
        cin >> a >> b; 
        --a, --b; 
        cout << ret[b][a] << '\n'; 
    }
    return 0; 
}