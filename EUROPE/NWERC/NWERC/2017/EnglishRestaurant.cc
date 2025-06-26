#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 500; 

struct Prob { 
  double num, den; 
  Prob() : num(0), den(0) {}; 
  void add(double _num, double _den) { 
    num += _num * _den; 
    den += _den; 
    return; 
  }
  double expected(void) { 
    if(den == 0) return 0; 
    return num / den; 
  } 
}; 
Prob E[maxf][maxf], dyn[maxf][maxf]; 

double Comb(int a, int b) {
#define COMB_MAXA 5000
#define COMB_MAXB 5000
  static double combmemo[COMB_MAXA + 1][COMB_MAXB + 1];
  if (a < b || b < 0) return 0;
  if (!a) return 1;
  double &ret = combmemo[a][b];
  if(ret > 0) return ret; 
  ret = Comb(a - 1, b - 1) + Comb(a - 1, b);
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N, G, T;
  cin >> N >> G >> T;
  vector<int> c(N + T + 1); 
  for(int i = 1; i <= N; i++) { 
    cin >> c[i];
    c[i] = min(c[i], G);  
  }
  for(int i = N + 1; i < N + T + 1; i++) { 
    c[i] = G; 
  }  
  sort(c.begin() + 1, c.end()); 
  for(int i = sz(c) - 1; i >= 0; i--) { 
    E[i][i].add(0, 1);
    for(int j = i + 1; j < sz(c); j++) if(i + T >= j) { 
       for(int k = i; k < j; k++) { 
         E[i][j].add(E[i][k].expected() + E[k + 1][j].expected() + (k + 1 <= N ? (c[k + 1] + c[i] + 1) / 2.0 : 0),
                     E[i][k].den * E[k + 1][j].den * Comb(j - i - 1, k - i) * (c[k + 1] - c[i])); 
       }
    }
  }
  for(int i = 0; i < sz(c); i++) { 
    if(i <= T) { dyn[i][i] = E[0][i]; }
    for(int k = 0; k <= T; k++) if(dyn[i][k].den > 0) { 
      for(int j = i + 1; j < sz(c); j++) { 
        if(k + j - i - 1 > T) continue; 
        dyn[j][k + j - i - 1].add(dyn[i][k].expected() + E[i + 1][j].expected(), 
                                  dyn[i][k].den * E[i + 1][j].den * Comb(k + j - i - 1, k));  
      } 
    }
  }
  cout << fixed << setprecision(10) << dyn[sz(c) - 1][T].expected() << '\n'; 
  return 0; 
}

/*  
   Let E(i, j) be the expected occupancy of range[i, j] then if we fixed the kth table, the number of ways 
   to choose k - 1 smaller table in the order that they come is Comb(j - i + 1, k - 1)

*/ 