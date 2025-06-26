#include "bits/stdc++.h"

using namespace std;

const double oo = 1e50; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M;
  vector<double>ang(N); 
  vector<pair<double, double>>pts(N);  
  for(int i = 0; i < N; i++) {
    cin >> ang[i];
    ang[i] = ang[i] * M_PI / 180; 
  }
  double ret = -oo; 
  for(int start = 0; start < N; start++) {
    vector<vector<double>>dyn(N, vector<double>(M, -oo));   
    dyn[start][0] = 0; 
    for(int j = 1; j < M; j++) { 
      for(int cand = start; cand < N; cand++) { 
        for(int next = cand + 1; next < N; next++) { 
          dyn[next][j] = max(dyn[next][j], dyn[cand][j - 1] + sin(ang[next] - ang[cand]));  
        }
      }  
    }
    for(int i = 0; i < N; i++) { 
      ret = max(ret, dyn[i][M - 1] + sin(ang[start] - ang[i])); 
    }
  }
  cout << fixed << setprecision(10) << ret * 500000.0 << '\n'; 
  return 0; 
}