#include "bits/stdc++.h"

using namespace std;

const int maxf = 100; 

double dyn[maxf][maxf][maxf], c[maxf][maxf];
int a[maxf]; 

double f(int i, int j, int k) {
  if(i == 0)  return k; 
  if(j == 0)  return 0; 
  if(dyn[i][j][k] != -1.0) return dyn[i][j][k]; 
  double &ret = dyn[i][j][k]; 
  ret = 0; 
  for(int ni = 0; ni <= i; ni++) { 
    ret += f(i - ni, j - 1, max(k, (ni + a[j] - 1) / a[j])) * c[i][ni] * pow(1.0 / j, ni) * pow(1.0 - 1.0 / j, i - ni); 
  }
  return ret; 
} 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  c[0][0] = 1;
  for(int i = 1; i < maxf; i++) { 
    for(int j = 0; j <= i; j++) { 
      c[i][j] = c[i - 1][j] + (j ? c[i - 1][j - 1] : 0); 
    }
  }
  int m, n;
  cin >> n >> m;
  for(int i = 1; i <= m; i++) { 
    cin >> a[i]; 
  }
  for(int i = 0; i < maxf; i++) for(int j = 0; j < maxf; j++) for(int k = 0; k < maxf; k++) { 
    dyn[i][j][k] = -1.0; 
  }
  cout << fixed << setprecision(15) << f(n, m, 0) << '\n'; 
  return 0;
}
 