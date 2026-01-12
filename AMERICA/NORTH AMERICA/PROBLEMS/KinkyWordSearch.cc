#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxn = 52; 

int n, m, k, dp[maxn << 1][9][maxn << 1][12][12]; 
char g[maxn][maxn]; 
string s; 

const int dx[8] = {-1, 1, -1, 1, 0, 0, -1, 1}; 
const int dy[8] = {-1, 1, 1, -1, -1, 1, 0, 0}; 

int search(int pos, int dir, int change, int x, int y) { 
 if(change < 0) return 0;    
 if(pos == sz(s)) return change == 0; 
 int &ret = dp[pos][dir][change][x][y]; 
 if(ret != -1) return ret; 
 ret = 0; 
 for(int ndir = 0; ndir < 8; ndir++) { 
  int nx = x + dx[ndir], ny = y + dy[ndir]; 
  if(0 <= nx && nx < n && 0 <= ny && ny < m && g[nx][ny] == s[pos]) { 
//cout << g[nx][ny] << " " << nx << " " << ny << " " << change - (dir < 9 && ndir != dir) << " " << dir << " " << ndir << '\n'; 
   ret |= search(pos + 1, ndir, change - (dir < 8 && ndir != dir), nx, ny);
   if(ret) return ret;  
  }
 }
 return ret; 
}


int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> n >> m; 
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < m; j++) { 
   cin >> g[i][j]; 
  }
 }
 cin >> k >> s;
 memset(dp, -1, sizeof dp); 
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < m; j++) { 
   if(g[i][j] == s[0] && search(1, 8, k, i, j)) { 
    cout << "Yes\n"; 
    return 0;    
   }
  }
 } 
 cout << "No\n"; 
 return 0;
}