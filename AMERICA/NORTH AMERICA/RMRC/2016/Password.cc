#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<double>Prob(N);
  string re;  
  for(int i = 0; i < N; i++) { 
    cin >> re >> Prob[i]; 
  }
  sort(Prob.rbegin(), Prob.rend()); 
  double ret = 0; 
  for(int i = 0; i < Prob.size(); i++) { 
    ret += Prob[i] * (i + 1); 
  }
  cout << fixed << setprecision(10) << ret << '\n'; 
  return 0; 
}

