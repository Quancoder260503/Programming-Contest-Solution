#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string S; 
  cin >> S;
  int N = sz(S); 
  stack<int>stk; 
  vector<int>l(N), r(N); 
  for(int i = 0; i < sz(S); i++) { 
   while(sz(stk) && S[stk.top()] <= S[i]) { 
    stk.pop(); 
   }
   l[i] = (stk.size() ? stk.top() : -1); 
   stk.push(i); 
  }
  while(stk.size()) stk.pop(); 
  for(int i = sz(S) - 1; i >= 0; i--) { 
   while(sz(stk) && S[stk.top()] < S[i]) { 
    stk.pop(); 
   }
   r[i] = (stk.size() ? stk.top() : -1); 
   stk.push(i); 
  }
  int64_t num = 0, den = 0; 
  for(int i = 0; i < N; i++) {
   if(r[i] != -1 && l[i] != -1) {
    num += 1LL * (i - l[i]) * (r[i] - i) * (S[i] - '0');  
   } else if(l[i] != -1) { 
    num += 1LL * (N - i) * (i - l[i]) * (S[i] - '0');
   } else if(r[i] != -1) { 
    num += 1LL * (i + 1) * (r[i] - i) * (S[i] - '0');
   } else { 
    num += 1LL * (N - i) * (i + 1) * (S[i] - '0'); 
   }
  }
  den = 1LL * N * (N + 1) / 2; 
  if(num >= den) { 
   cout << num / den << " ";
   if(num % den > 0) {
    num = num % den; 
    int64_t g = gcd(num, den); 
    cout << num / g << "/" << den / g << '\n';  
   } 
  } else { 
   if(num == 0) cout << num << '\n'; 
   else { 
    int64_t g = gcd(num, den); 
    cout << num / g << "/" << den / g << '\n';  
   }
  }
  return 0;
}