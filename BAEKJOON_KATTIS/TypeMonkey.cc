#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

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

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Tc, K, L, N; 
  cin >> Tc;
  cout << fixed << setprecision(10); 
  for(int _case = 0; _case < Tc; _case++) { 
    string S, T; 
    cin >> K >> L >> N >> S >> T;
    vector<int>freq(26);  
    for(int i = 0; i < sz(S); i++) {
      freq[S[i] - 'A']++; 
    }
    vector<vector<vector<double>>>dp(2, vector<vector<double>>(L + 1, vector<double>(N - L + 7))); 
    dp[0][0][0] = 1.; 
    vector<int>kmp = prefix_function(T); 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < L + 1; j++) { 
        for(int k = 0; k < N - L + 7; k++) { 
          dp[(i + 1) & 1][j][k] = 0; 
        }
      }
      for(int state = 0; state <= L; state++) { 
        for(int j = 0; j < 26; j++) { 
          if(freq[j] == 0) continue; 
          int nextState = get_next(kmp, T, state, char(j + 'A')); 
          for(int numOcc = 0; numOcc < N - L + 1; numOcc++) { 
            dp[(i + 1) & 1][nextState][numOcc + (nextState == L)] += dp[i & 1][state][numOcc] * freq[j] / K; 
          }
        }
      }
    }
    double expected = 0.; 
    for(int i = 0; i <= L; i++) { 
      for(int j = 0; j < N - L + 2; j++) { 
        expected += dp[N & 1][i][j] * j; 
      } 
    }
    for(int i = 0; i < sz(dp); i++) { 
      for(int j = 0; j < sz(dp[0]); j++) { 
        for(int k = 0; k < sz(dp[0][0]); k++) { 
          dp[i][j][k] = 0; 
        }
      }
    }
    dp[0][0][0] = 1; 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < L + 1; j++) { 
        for(int k = 0; k < N - L + 7; k++) { 
          dp[(i + 1) & 1][j][k] = 0; 
        }
      }
      for(int state = 0; state <= L; state++) { 
        for(int j = 0; j < 26; j++) { 
          if(freq[j] == 0) continue; 
          int nextState = get_next(kmp, T, state, char(j + 'A')); 
          for(int numOcc = 0; numOcc < N - L + 1; numOcc++) {
            if(dp[i & 1][state][numOcc] > 0) { 
              dp[(i + 1) & 1][nextState][numOcc + (nextState == L)] = 1; 
            } 
          }
        }
      }
    }
    double ret = 0; 
    for(int i = N - L + 1; i >= 0; i--) {
      int flag = false;  
      for(int state = 0; state <= L; state++) { 
        if(dp[N & 1][state][i] > 0) { 
          flag = true;
          break; 
        }
      }
      if(flag) { 
        ret = i; 
        break; 
      }
    }
    ret = ret - expected; 
    cout << "Case #" << _case + 1 << ": " << ret << '\n'; 
  }
  return 0; 
}
