#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int mod = 1e9 + 7;

vector<vector<int64_t>>dyn[2][2]; 
string L, R, X;
int K;  

vector<int> prefix_function(const string &s) {
  int n = sz(s);
  vector<int> pi(n + 1);
  for (int i = 2; i <= n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i - 1] != s[j]) j = pi[j];
    if (s[i - 1] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

int get_next(vector<int> &pi, string &s, int pos, char c) {
  if (pos == sz(s)) pos = pi[pos];
  while (pos > 0 && c != s[pos]) pos = pi[pos];
  if (s[pos] == c) pos++;
  return pos;
}

int64_t calc(vector<vector<int>> &nxt, vector<int> &v, const string &s) { 
  dyn[0][true][0][0] = 1; 
  int64_t ret = 0; 
  for(int pos = 0; pos < sz(s); pos++) { 
    for(int sum = 0; sum <= K; sum++) { 
      for(int state = 0; state < sz(nxt); state++) { 
        for(int isEqual = 0; isEqual < 2; isEqual++) { 
          if(dyn[pos & 1][isEqual][state][sum] == -1) continue; 
          int digitBound = (isEqual ? (s[pos] - '0') : 9); 
          for(int digit = 0; digit <= digitBound; digit++) { 
            int nextState = nxt[state][digit]; 
            int nextSum = sum + v[nextState]; 
            if(nextSum > K) continue; 
            int64_t &ret = dyn[(pos + 1) & 1][isEqual && (digit == digitBound)][nextState][nextSum];
            if(ret == -1) ret = 0; 
            (ret += dyn[pos & 1][isEqual][state][sum]) %= mod; 
          }
        }
      } 
    }
    for(int sum = 0; sum <= K; sum++) { 
      for(int state = 0; state < sz(nxt); state++) { 
        for(int isEqual = 0; isEqual < 2; isEqual++) { 
          if(pos == sz(s) - 1 && dyn[sz(s) & 1][isEqual][state][sum] != -1) { 
            (ret += dyn[sz(s) & 1][isEqual][state][sum]) %= mod; 
            dyn[sz(s) & 1][isEqual][state][sum] = -1; 
          } 
          dyn[pos & 1][isEqual][state][sum] = -1;   
        }
      }
    }
  }
  return ret; 
}


int checkString(vector<vector<int>> &nxt, vector<int> &v) { 
  int start = 0, sum = 0; 
  for(int i = 0; i < sz(L); i++) { 
    start = nxt[start][L[i] - '0']; 
    sum += v[start]; 
  }
  return sum <= K; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> L >> R >> X >> K; 
  vector<int>kmp = prefix_function(X); 
  vector<int>v(sz(kmp)); 
  for(int i = 1; i < sz(kmp); i++) { 
    cin >> v[i]; 
  }
  vector<vector<int>> nxt(sz(kmp), vector<int>(10)); 
  for(int i = 0; i < sz(kmp); i++) { 
    for(int j = 0; j < 10; j++) { 
      nxt[i][j] = get_next(kmp, X, i, char(j + '0')); 
    }
  }
  for(int i = 0; i < sz(kmp); i++) { 
    v[i] += v[kmp[i]];
  }
  for(int i = 0; i < 2; i++) { 
    for(int j = 0; j < 2; j++) { 
      dyn[i][j].resize(sz(nxt), vector<int64_t>(K + 1, -1)); 
    }
  }
  int64_t ret = 0;
  (ret += mod + calc(nxt, v, R) - calc(nxt, v, L) + checkString(nxt, v)) %= mod;
  cout << ret << '\n'; 
  return 0; 
}