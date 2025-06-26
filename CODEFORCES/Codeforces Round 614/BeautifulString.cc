#include "bits/stdc++.h"

using namespace std; 

int main() {
  int T;
  string S;  
  for(cin >> T; T--; ) { 
    cin >> S;
    int last = -1, N = S.size(); 
    string ret; 
    for(int i = 0; i < N; i++) { 
      if(S[i] != '?') {
        if(last == -1 && i > 0) { 
           string c = (S[i] == 'a' ? "bc" : (S[i] == 'b' ? "ca" : "ab")); 
           for(int k = 0; k < i; k++) { 
             ret += c[k & 1]; 
           }
        }
        last = i; 
        int j = i + 1;
        ret += S[i]; 
        while(j < N && S[j] == '?') { j++; }
        if(j == i + 1) { 
          continue; 
        }
        if(j < N) { 
          if(S[j] == S[i]) {
            string c = (S[i] == 'a' ? "bc" : (S[i] == 'b' ? "ca" : "ab")); 
            for(int k = 0; k < j - i - 1; k++) { 
              ret += c[k & 1]; 
            }
          }
          else { 
            string c; 
            for(char ch = 'a'; ch <= 'c'; ch++) { 
              if(ch == S[i]) {
                for(char ch2 = 'a'; ch2 <= 'c'; ch2++) { 
                  if(ch2 == S[j]) {
                    c += ch2; 
                    for(char ch3 = 'a'; ch3 <= 'c'; ch3++) { 
                      if(ch3 == ch || ch3 == ch2) continue; 
                      c += ch3; 
                    } 
                    break; 
                  }
                } 
                break; 
              }
            }
            if((j - i) % 2 == 0) reverse(c.begin(), c.end()); 
            for(int k = 0; k < j - i - 1; k++) { 
              ret += c[k & 1]; 
            }
          }  
        }
        else {
          for(int k = i + 1; k < j; k++) { 
            for(char ch = 'a'; ch <= 'c'; ch++) { 
              if(ch != ret.back()) { 
                ret += ch; 
                break; 
              }
            }
          }
        }
        i = j - 1; 
      } 
    } 
    for(int i = 0; i + 1 < ret.size(); i++) { 
      if(ret[i] == ret[i + 1]) { 
        ret = "-1"; 
        break; 
      }
    }
    if(ret.size() == 0) { 
      string c = "ab"; 
      for(int i = 0; i < N; i++) {
        ret += c[i & 1]; 
      }
    }
    cout << ret << '\n';
  } 
  return 0; 
}