#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int solve(int K, int64_t C, string &first, string &middle, string &last) {
  int64_t len = sz(first); 
  C++; 
  if(C <= len) { 
    cout << first[C - 1] << '\n'; 
    return 0; 
  }
  len += 3LL * K; 
  if(C <= len) {
    string c = "SON"; 
    cout << c[(C - sz(first) - 1) % 3] << '\n'; 
    return 0; 
  }
  C = C - len; 
  len = 1LL * sz(first) * K + 3LL * K * (K - 1) / 2 + sz(middle) + 1LL * sz(last) * K; 
  if(C <= len) {
    len = len - sz(middle) - 1LL * sz(last) * K; 
    if(C <= len) { 
      auto func = [&](int x) { 
        int64_t sum = len - (1LL * sz(first) * x + 3LL * x * (x - 1) / 2);
        return sum <= C; 
      }; 
      int lo = 1, hi = K; 
      while(lo < hi) { 
        int mid = (lo + hi) / 2; 
        if(func(mid)) {
          hi = mid; 
        } else { 
          lo = mid + 1; 
        }
      } 
      C = C - (len - 1LL * sz(first) * lo - 3LL * lo * (lo - 1) / 2); 
      if(C <= 1LL * sz(first)) { 
        cout << first[(C - 1 + sz(first)) % sz(first)] << '\n';  
      }
      else { 
        string c = "SON"; 
        cout << c[(C - 1 - sz(first)) % 3] << '\n'; 
      }
      return 0;
    }
    C = C - len; 
    len = sz(middle); 
    if(C <= len) { 
      cout << middle[C - 1] << '\n'; 
    }
    else { 
      C = C - len; 
      int lo = 1, hi = K; 
      while(lo < hi) { 
        int mid = (lo + hi + 1) / 2; 
        if(C >= 1LL * sz(last) * mid) { 
          lo = mid; 
        }
        else { 
          hi = mid - 1;   
        }
      }
      C = C - 1LL * sz(last) * lo;  
      cout << last[(C - 1 + sz(last)) % sz(last)] << '\n'; 
    }
  } else { 
    cout << last[C - len - 1] << '\n'; 
  }
  return 0; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0);
  cout.tie(0); 
  int K; int64_t C; 
  string first, middle, last;
  cin >> K >> C;
  cin >> first >> middle >> last; 
  solve(K, C, first, middle, last);  
  return 0; 
}