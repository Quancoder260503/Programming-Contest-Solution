#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  string S;
  cin >> S; 
  if(sz(S) < 26) { 
    cout << -1 << '\n'; 
  }
  else { 
    S = " " + S; 
    vector<vector<int>>next(sz(S), vector<int>(26, sz(S) + 1));
    for(int i = 1; i < sz(S); i++) { 
      for(int j = i - 1; j >= 0; j--) { 
        next[j][S[i] - 'a'] = i; 
        if(S[i] == S[j]) break; 
      }
    }
    vector<vector<int>>dp(sz(S), vector<int>(26, -1)); 
    function<int(int, int)> canBuild = [&](int pos, int c) -> int { 
      if(pos > sz(S)) return oo; 
      if(pos == sz(S)) return (c == 26 ? 0 : oo); 
      if(c == 26) return 0; 
      int &ret = dp[pos][c]; 
      if(ret != -1) return ret; 
      ret = canBuild(next[pos][c], c + 1);
      if(pos + 1 < sz(S)) { 
        int j = pos + 1; 
        while(j < sz(S) && S[j] > char(c + 'a')) j++; 
        if(j < sz(S)) { 
          ret = min(ret, (char(c + 'a') - S[j]) + canBuild(j, c + 1));
        } 
      } 
      return ret; 
    };
    function<void(int, int)> rec = [&](int pos, int c) { 
      if(pos == sz(S) || c == 26) return; 
      canBuild(pos, c);  
      if(dp[pos][c] == canBuild(next[pos][c], c + 1)) { 
        rec(next[pos][c], c + 1); 
      }
      else {
        if(pos + 1 < sz(S)) { 
          int j = pos + 1; 
          while(j < sz(S) && S[j] > char(c + 'a')) j++; 
          S[j] = char(c + 'a'); 
          rec(j, c + 1); 
        } 
      }
    }; 
    if(canBuild(0, 0) >= oo) { 
      cout << -1 << '\n'; 
    }
    else { 
      rec(0, 0);
      cout << S.substr(1) << '\n';  
    }
  }
  return 0; 
}