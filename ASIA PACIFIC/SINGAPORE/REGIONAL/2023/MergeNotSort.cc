#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<int>a(2 * N); 
 for(int i = 0; i < 2 * N; i++) { 
  cin >> a[i]; 
 }
 vector<int>nxt(2 * N, 2 * N);
 stack<int>stk; 
 for(int i = 2 * N - 1; i >= 0; i--) { 
  while(sz(stk) && a[i] > a[stk.top()]) { 
   stk.pop(); 
  }
  if(sz(stk)) nxt[i] = stk.top(); 
  stk.push(i); 
 } 
 vector<vector<int>>dp(2 * N, vector<int>(N + 1, -1)); 
 vector<vector<pair<int, int>>>par(2 * N, vector<pair<int, int>>(N + 1, {-1, -1})); 
 function<int(int, int)> f = [&](int pos, int weight) -> int { 
  if(pos == 2 * N) return weight == N; 
  int &ret = dp[pos][weight]; 
  if(ret != -1) return ret; 
  ret = 0;
  int nWeight = pos - weight; 
  if(weight + nxt[pos] - pos <= N) { 
   ret |= f(nxt[pos], weight + nxt[pos] - pos); 
   if(ret) { 
    par[pos][weight] = {nxt[pos], weight + nxt[pos] - pos}; 
    return ret; 
   }
  }
  if(nWeight + nxt[pos] - pos <= N) { 
   ret |= f(nxt[pos], weight); 
   if(ret) { 
    par[pos][weight] = {nxt[pos], weight}; 
    return ret; 
   }
  }
  return ret; 
 }; 
 int ret = f(0, 0); 
 if(ret) { 
  int pos = 0, weight = 0; 
  vector<int>sa, sb; 
  while(pos < 2 * N) { 
   if(par[pos][weight].second == weight + nxt[pos] - pos) { 
    for(int i = pos; i < nxt[pos]; i++) { 
     sb.push_back(i); 
    }
   }
   else { 
    for(int i = pos; i < nxt[pos]; i++) { 
     sa.push_back(i); 
    }
   }
   auto [nPos, nWeight] = par[pos][weight]; 
   pos = nPos, weight = nWeight; 
  }
  for(int i = 0; i < sz(sa); i++) { 
    cout << a[sa[i]] << " "; 
  }
  cout << '\n'; 
  for(int i = 0; i < sz(sb); i++) { 
    cout << a[sb[i]] << " "; 
  }
  cout << '\n'; 
 }
 else { 
  cout << -1 << '\n'; 
 }
 return 0; 
}