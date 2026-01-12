#include "bits/stdc++.h"
 
using namespace std; 
 
const int LOG = 31; 
 
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M;
  vector<vector<int>>nxt(N, vector<int>(LOG)); 
  for(int i = 0; i < N; i++) { 
   cin >> nxt[i][0]; 
   --nxt[i][0]; 
  } 
  for(int j = 1; j < LOG; j++) { 
   for(int i = 0; i < N; i++) { 
    nxt[i][j] = nxt[nxt[i][j - 1]][j - 1]; 
   } 
  } 
  auto jump = [&](int x) { 
   int c = x; 
   for(int i = 0; i < LOG; i++) { 
    if(M >> i & 1) { 
     c = nxt[c][i]; 
    } 
   }
   return c; 
  };  
  vector<int>cnt(N); 
  for(int i = 0; i < N; i++) { 
   cnt[jump(i)]++; 
  } 
  pair<int, int>ret = {-1, N}; 
  for(int i = 0; i < N; i++) { 
   if(ret.first < cnt[i]) { 
    ret = make_pair(cnt[i], i); 
   } else if(ret.first == cnt[i]) { 
    ret.second = min(ret.second, i); 
   } 
  } 
  cout << ret.second + 1 << " " << ret.first << '\n'; 
  return 0;
}