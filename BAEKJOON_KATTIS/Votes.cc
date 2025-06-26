#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, Q; 
  cin >> Q; 
  cout << fixed << setprecision(10); 
  for(int iter = 0; iter < Q; iter++) { 
    cin >> N >> M; 
    vector<vector<double>>dyn(N + 1, vector<double>(M + 1, -1)); 
    function<double(int, int)> memo = [&](int rem_a, int rem_b) { 
       if(rem_a < N && rem_b < M && N - rem_a <= M - rem_b) return 0.; 
       if(rem_a == 0) return 1.; 
       double &ret = dyn[rem_a][rem_b];
       if(ret >= 0) return ret; 
       ret = 1.0 * rem_a / (rem_a + rem_b) * memo(rem_a - 1, rem_b) 
           + 1.0 * rem_b / (rem_a + rem_b) * memo(rem_a, rem_b - 1);  
       return ret; 
    }; 
    cout << "Case #" << iter + 1 << ": " << memo(N, M) << '\n'; 
  }
  return 0; 
}