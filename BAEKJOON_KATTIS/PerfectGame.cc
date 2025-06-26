#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T, N; 
  cin >> T; 
  for(int _case = 0; _case < T; _case++) {
    cin >> N; 
    vector<int>Prob(N), L(N); 
    for(int i = 0; i < N; i++) { 
      cin >> L[i]; 
    }
    for(int i = 0; i < N; i++) { 
      cin >> Prob[i]; 
      Prob[i] = 100 - Prob[i]; 
    }
    vector<int>ord(N); 
    iota(ord.begin(), ord.end(), 0); 
    stable_sort(ord.begin(), ord.end(), [&](int x, int y) { 
      int isEqual = (L[x] * 100 + L[y] * Prob[x]) == (L[y] * 100 + L[x] * Prob[y]);
      return isEqual ? x < y : (L[x] * 100 + L[y] * Prob[x]) < (L[y] * 100 + L[x] * Prob[y]); 
    }); 
    cout << "Case #" << _case + 1 << ": "; 
    for(auto &x : ord) { cout << x << " "; }
    cout << '\n'; 
  }
  return 0; 
}