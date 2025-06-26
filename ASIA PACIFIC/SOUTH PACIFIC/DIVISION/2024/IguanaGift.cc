#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
  string S; 
  cin >> S; 
  int ret = 1; 
  for(int i = 0; i + 1 < sz(S); i++) { 
    int curr = 0; 
    if(S[i] == S[i + 1]) { 
      int dist = 0, cnt = 0; 
      while(i - dist >= 0 && i + dist + 1 < sz(S) && S[i - dist] == S[i + 1 + dist]) { 
        dist++; 
        cnt += 2; 
      }
      if(i + dist + 1 == sz(S)) { 
        curr = max(curr, cnt); 
      } 
    }
    if(i > 0 && S[i - 1] == S[i + 1]) { 
      int dist = 0, cnt = 1; 
      while(i - dist > 0 && i + 1 + dist < sz(S) && S[i - 1 - dist] == S[i + 1 + dist]) { 
        dist++; 
        cnt += 2; 
      } 
      if(i + dist + 1 == sz(S)) { 
        curr = max(curr, cnt); 
      } 
    }
    ret = max(ret, curr); 
  } 
  cout << sz(S) - ret << '\n'; 
  return 0;
}