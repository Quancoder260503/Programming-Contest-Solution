#include "bits/stdc++.h"

using namespace std; 

const int maxn = 60; 
const int oo = 1e9; 

int dp[2][maxn][maxn][maxn]; 


int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int nState, nTerminate, m; 
 cin >> nState >> nTerminate >> m; 
 vector<vector<int>>nxt(nState + 1, vector<int>(256)); 
 vector<int>term(nState + 1);
 for(int i = 0, x; i < nTerminate; i++) { 
  cin >> x; 
  term[x] = 1; 
 }
 for(int i = 0, s1, s2; i < m; i++) { 
  char c;
  cin >> s1 >> c >> s2;   
  nxt[s1][c] = s2; 
 }

 using T = pair<int, array<int, 4>>; 
 priority_queue<T, vector<T>, greater<T>>pq; 
 auto enqueue = [&](int isDiff, int doneL, int x, int y, int d) { 
  if(dp[isDiff][doneL][x][y] > d) { 
   pq.push({dp[isDiff][doneL][x][y] = d, {isDiff, doneL, x, y}}); 
  }
 }; 
 memset(dp, 63, sizeof dp); 
 dp[0][0][1][1] = 0; 
 pq.push({0, {0, 0, 1, 1}}); 
 int ret = oo; 
 while(pq.size()) { 
  auto [d, states] = pq.top(); 
  auto [isDiff, doneL, s1, s2] = states; 
  pq.pop(); 
  if(dp[isDiff][doneL][s1][s2] != d) continue; 
  if(isDiff && term[s1] && term[s2]) ret = min(ret, d); 
  for(char c = 'A'; c <= 'Z'; c++) { 
   if(nxt[s1][c] && nxt[s2][c]) { 
    enqueue(isDiff, 0, nxt[s1][c], nxt[s2][c], d + 2); 
   }
  }
  if(isDiff) { 
   for(char c = 'a'; c <= 'z'; c++) { 
    if(!doneL && nxt[s1][c]) { 
     enqueue(isDiff, doneL, nxt[s1][c], s2, d + 1);    
    }
    if(nxt[s2][c]) { 
     enqueue(isDiff, doneL, s1, nxt[s2][c], d + 1); 
    } 
   } 
  }
  if(!isDiff && !doneL) { 
   for(char c = 'a'; c <= 'z'; c++) { 
    if(nxt[s1][c] && nxt[s2][c]) { 
      enqueue(isDiff, doneL, nxt[s1][c], nxt[s2][c], d + 2); 
    }
   }
   for(char c1 = 'a'; c1 <= 'z'; c1++) { 
    for(char c2 = 'a'; c2 <= 'z'; c2++) { 
     if(c1 != c2 && nxt[s1][c1] && nxt[s2][c2]) { 
      enqueue(1, doneL, nxt[s1][c1], nxt[s2][c2], d + 2);   
     }    
    }
   }
   for(char c2 = 'a'; c2 <= 'z'; c2++) { 
    if(nxt[s2][c2]) { 
     enqueue(1, 1, s1, nxt[s2][c2], d + 1);    
    }
   }
  }
 }
 if(ret >= oo) cout << -1 << '\n'; 
 else cout << ret << '\n'; 
 return 0; 
} 