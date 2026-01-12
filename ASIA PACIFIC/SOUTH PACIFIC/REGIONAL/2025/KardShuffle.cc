#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main() {
 int n, x; 
 cin >> n >> x; 
 auto gL = [&](int u) { 
  if(u % 2 == 1) return (u + 1) / 2; 
  else return n + u / 2;
 }; 
 auto gR = [&](int u) { 
  if(u % 2 == 0) return u / 2; 
  else return n + (u + 1) / 2; 
 };
 queue<int>q;
 vector<int>dp(2 * n + 1, -1);
 vector<pair<int, char>>par(2 * n + 1); 
 dp[1] = 0;  
 q.push(1); 
 while(q.size()) { 
  int u = q.front(); 
  q.pop(); 
//  if(u == x) break; 
  int v = gL(u); 
  if(dp[v] == -1) { 
   dp[v] = dp[u] + 1; 
   par[v] = {u, 'L'}; 
   q.push(v);
   if(v == x) break;  
  }
  v = gR(u); 
  if(dp[v] == -1) { 
   dp[v] = dp[u] + 1; 
   par[v] = {u, 'R'}; 
   q.push(v);
   if(v == x) break;  
  }
 }
 if(dp[x] == -1) cout << -1 << '\n'; 
 else { 
  cout << dp[x] << '\n'; 
  int curr = x; 
  string ret; 
  while(curr != 1) { 
   ret += par[curr].second; 
   curr = par[curr].first; 
  }
  cout << ret << '\n'; 
 }
 return 0;
}
