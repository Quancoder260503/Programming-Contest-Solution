#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {  
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  string S; 
  cin >> S;
  string dna = "ATGC"; 
  vector<vector<int>>prefix(sz(S), vector<int>(4));  
  for(int i = 0; i < sz(S); i++) { 
    for(int j = 0; j < 4; j++) { 
      prefix[i][j] = (i ? prefix[i - 1][j] : 0); 
    }
    prefix[i][dna.find(S[i])]++; 
  }
  int Q;
  cin >> Q; 
  for(int i = 0, L, R; i < Q; i++) { 
    cin >> L >> R;
    --L, --R; 
    string cc = {'A', 'T', 'G', 'C'}; 
    sort(cc.begin(), cc.end(), [&](char a, char b) { 
      return (prefix[R][dna.find(a)] - (L ? prefix[L - 1][dna.find(a)] : 0)) > 
             (prefix[R][dna.find(b)] - (L ? prefix[L - 1][dna.find(b)] : 0)); 
    }); 
    cout << cc << '\n'; 
  }
  return 0; 
}