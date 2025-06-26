#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  auto solve = [&](string S) { 
    if(S == "22" || S.size() == 1) return S;
    int sum = 0; 
    for(int i = 0; i <= S.size(); i++) { 
      if((i == S.size() || S[i] > '2') && (sum & 2))      S.insert(i, "2"); 
      else if((i == S.size() || S[i] > '4') && (sum & 4)) S.insert(i, "4"); 
      sum += S[i] - '0'; 
    }
    sum = 0; 
    for(int i = 0; i < S.size(); i++) { 
      sum += S[i] - '0'; 
    }
    while(sum & (sum - 1)) { 
      S += "8"; 
      sum += 8; 
    }
    return S; 
  }; 
  int Q; 
  cin >> Q; 
  for(int iter = 0; iter < Q; iter++) { 
    string S; 
    cin >> S; 
    cout << solve(S) << '\n'; 
  }
  return 0; 
}