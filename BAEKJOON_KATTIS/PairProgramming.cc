#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7; 

#define ctoi(x) x - '0'
#define sz(x) int(x.size())

string parseString(const string &a) { 
 string A; 
 for(auto s : a) { 
   if(s == '1') continue; 
   if(s == '0') A.clear(); 
   if(s != '+') { 
    A += '2'; 
    continue; 
   }
   A += s; 
  }
  return A;
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, T;
  for(cin >> T; T--; ) { 
    cin >> N; 
    string a, b; 
    cin >> a >> b; 
    string A = parseString(a); 
    string B = parseString(b); 
    vector<vector<vector<int64_t>>> dyn(sz(A) + 1, vector<vector<int64_t>>(
                                        sz(B) + 1, vector<int64_t>(2))); 
    dyn[0][0][0] = 1; 
    for(int i = 0; i <= sz(A); i++) { 
      for(int j = 0; j <= sz(B); j++) { 
        for(int k = 0; k < 2; k++) { 
          if(j < sz(B)) { 
            (dyn[i][j + 1][1] += dyn[i][j][k]) %= MOD; 
          }
          if(k == 0) { 
            if(i < sz(A)) { 
              (dyn[i + 1][j][0] += dyn[i][j][k]) %= MOD; 
            } 
          }
          else { 
            if(j > 0 && i < sz(A) && B[j - 1] != A[i]) { 
              (dyn[i + 1][j][0] += dyn[i][j][k]) %= MOD; 
            }
          } 
        }
      }
    }
    cout << (dyn[sz(A)][sz(B)][0] + dyn[sz(A)][sz(B)][1]) % MOD << '\n'; 
  }
  return 0; 
}

/* dp[i][j][k] = {number of ways to interleave the ith prefix of a and jth prefix of b
                        given that the last merge was done by the first player}

   dp[i][j][1] = (dyn[i][j - 1][1] + dyn[i - 1][j][0])
   dp[i][j][0] = (dyn[i - 1][j][0] + dyn[i][j - 1][1])
*/ 