#include "bits/stdc++.h"

using namespace std; 

#pragma GCC optimize("O3")
#pragma GCC optimization("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 string S; 
 int N; 
 cin >> N >> S; 
 S = " " + S;
 N = sz(S); 
 vector<int>nxt(N), prefix(N), cc(N, N); 
 int last = N; 
 for(int i = N - 1; i >= 0; i--) {
  nxt[i] = last; 
  last = (S[i] == '1' ? i : last); 
 }
 for(int i = 1; i < N; i++) { 
  prefix[i] = prefix[i - 1] + (S[i] == '0'); 
  cc[prefix[i]] = min(cc[prefix[i]], i); 
 }
 int ans = N - 1 - prefix[N - 1]; 
 int turn = 0; 
 for(int d = (N - 1) / 2; d > 0; d--) { 
  int start = 0, cnt = 0; 
  while(start < N && prefix[start] + d < N) { 
   int pos = cc[prefix[start] + d]; 
   if(pos >= N) break; 
   start = (S[pos] == '1' ? pos : nxt[pos]);
   cnt++;  
  }
  if(cnt > 1) { 
    ans = max(ans, cnt * d + (cnt - 1)); 
    turn++; 
    if(turn == 100000) break; 
  } 
 }
 turn = 0; 
 for(int d = 1; d <= (N - 1) / 2; d++) { 
  int start = 0, cnt = 0; 
  while(start < N && prefix[start] + d < N) { 
   int pos = cc[prefix[start] + d]; 
   if(pos >= N) break; 
   start = (S[pos] == '1' ? pos : nxt[pos]);
   cnt++;  
  }
  if(cnt > 1) { 
    ans = max(ans, cnt * d + (cnt - 1)); 
    turn++; 
    if(turn == 1000) break; 
  } 
 }
 cout << ans << '\n'; 
 return 0; 
}