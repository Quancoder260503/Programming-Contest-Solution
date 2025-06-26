#include "bits/stdc++.h"

using namespace std;

const int oo = 1e6; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int tc; 
  cin >> tc;
  string text;  
  cin.ignore(); 
  for(int iter = 0; iter < tc; iter++) { 
    getline(cin, text); 
    string S = text; 
    int N = S.size();
    vector<vector<int>>dyn(N, vector<int>(N, -1)); 
    function<int(int, int)> memo = [&](int i, int j) { 
        if(i == j) return 2; 
        if(i >  j) return 0; 
        int &ret = dyn[i][j];
        if(ret != -1) return ret; 
        ret = 2 * (j - i + 1);  
        for(int k = i; k <= j; k++) if(S[j] == S[k]) {
          ret = min(ret, memo(i, k) + memo(k + 1, j - 1)); 
        }
        ret = min(ret, 2 + memo(i, j - 1)); 
        return ret; 
    }; 
    cout << N + memo(0, N - 1) << '\n'; 
  }
  return 0; 
}