#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<double>Prob(N); 
  for(int i = 0; i < N; i++) { 
    cin >> Prob[i]; 
  }
  vector<vector<double>>dyn(N + 1, vector<double>(N + 1, -1)); 
  function<double(int, int)> memo = [&](int pos, int head) -> double { 
    if(pos == N) return (head > N - head); 
    double &ret = dyn[pos][head]; 
    if(ret >= 0) return ret; 
    ret = Prob[pos] * memo(pos + 1, head + 1) + 
         (1.0 - Prob[pos]) * memo(pos + 1, head);
    return ret;  
  }; 
  cout << fixed << setprecision(10) << memo(0, 0) << '\n'; 
  return 0; 
}