#include "bits/stdc++.h"

using namespace std; 

const int MAX_T = 1e6 + 10; 
const int oo = 1e9; 

int pre[MAX_T]; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K; 
 cin >> N >> K; 
 vector<array<int, 2>>trips(N); 
 vector<array<int, 3>>inter(K); 
 memset(pre, -1, sizeof(pre)); 
 for(int i = 0; i < N; i++) { 
  cin >> trips[i][0] >> trips[i][1]; 
  trips[i][0]++; 
  pre[trips[i][0]] = i; 
 }
 for(int i = 0; i < K; i++) { 
  cin >> inter[i][0] >> inter[i][1] >> inter[i][2]; 
 } 
 for(int i = 1; i < MAX_T; i++) { 
  if(pre[i] == -1) pre[i] = pre[i - 1]; 
 }
 vector<int>dp(N, -1); 
 function<int(int)> memo = [&](int curr) { 
  if(curr == -1) return 0; 
  int &ret = dp[curr]; 
  if(ret != -1) return ret; 
  ret = trips[curr][1] + memo(curr - 1); 
  for(int pass = 0; pass < K; pass++) { 
   ret = min(ret, inter[pass][2] + memo(max(curr - inter[pass][1], 
                                            pre[max(0, trips[curr][0] - inter[pass][0])]))); 
  }
  return ret; 
 }; 
 cout << memo(N - 1) << '\n'; 
 return 0; 
}