#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
 int N, Q; 
 cin >> N >> Q; 
 vector<int>h(N); 
 for(int i = 0; i < N; i++) { 
  cin >> h[i]; 
 }
 vector<int>nxt(N); 
 stack<int>stk; 
 for(int i = N - 1; i >= 0; i--) { 
  while(sz(stk) && h[stk.top()] <= h[i]) { 
   stk.pop(); 
  }
  nxt[i] = (sz(stk) ? stk.top() : -1); 
  stk.push(i); 
 }
 vector<int>ans(N); 
 char c; 
 function<int(int)> find_next = [&](int curr) -> int { 
  if(nxt[curr] == -1) return -1; 
  if(ans[nxt[curr]] == h[nxt[curr]]) return nxt[curr] = find_next(nxt[curr]);
  return nxt[curr];  
 }; 
 for(int iter = 0; iter < Q; iter++) { 
  cin >> c;
  if(c == '+') { 
   int st, amt; 
   cin >> st >> amt; 
   --st; 
   for(int curr = st; curr != -1 && amt > 0; curr = find_next(curr)) { 
    if(ans[curr] < h[curr]) { 
     int rem = h[curr] - ans[curr]; 
     ans[curr] += min(rem, amt); 
     amt = max(0, amt - rem); 
    }
   }
  } else { 
    int pos; 
    cin >> pos; 
    cout << ans[--pos] << '\n'; 
  }
 }
 return 0; 
}