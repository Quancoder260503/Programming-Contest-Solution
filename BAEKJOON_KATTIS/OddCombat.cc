#include "bits/stdc++.h"

using namespace std; 

void solve(void) {
 int N, L; 
 double prob; 
 cin >> N >> L >> prob; 
 vector<double>cc; 
 for(int i = 0; i < N + 1; i++) { 
  if(i < L) { 
   cc.push_back(0); 
  } else {
    double h = 0, c = 1;  
    for(int j = 1; j <= L; j++) { 
     h += prob * c * cc[i - j]; 
     c *= (1. - prob); 
    }
    h += c; 
    cc.push_back(h); 
  }
 }
 cout << cc[N] << '\n'; 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  cout << fixed << setprecision(10); 
  for(cin >> T; T--;) { 
   solve(); 
  }
  return 0; 
}