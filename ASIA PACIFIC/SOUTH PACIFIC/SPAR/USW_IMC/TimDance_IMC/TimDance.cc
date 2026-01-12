#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <iomanip> 
#include <numeric> 
#include <set> 
#include <cstring> 
#include <functional> 

#define sz(x) int(x.size())
#define ll long long

using namespace std; 

const int maxn = 1e6 + 10; 
const int MOD = 1e9 + 7; 

vector<int>row_adj[maxn], col_adj[maxn]; 
int R, C, N, vis_row[maxn], vis_col[maxn]; 
set<int> row_travs, col_travs;

int dfs(int u, int row) { 
  int cc = 0;
  if(row) { 
   for(auto c : row_adj[u]) { 
    if(!vis_col[c]) { 
     vis_col[c] = 1; 
     cc += dfs(c, false);     
    }
   }
  } else { 
   for(auto r : col_adj[u]) { 
    if(!vis_row[r]) { 
     vis_row[r] = 1;  
     cc += dfs(r, true);    
    }
   }
  }
  return cc + 1; 
}

int main(void) {
 cin >> R >> C >> N; 
 memset(vis_col, 0, sizeof vis_col); 
 memset(vis_row, 0, sizeof vis_row); 
 for(int i = 0, r, c; i < N; i++) { 
  cin >> r >> c; 
  row_adj[r].push_back(c); 
  col_adj[c].push_back(r);
  row_travs.insert(r); 
  col_travs.insert(c);     
 } 
 int ans = 0, o = 1; 
 for(auto r : row_travs) { 
  if(!vis_row[r]) { 
   vis_row[r] = 1;  
   int cc_size = dfs(r, true);
   ans += cc_size - 1; 
   if(cc_size % 2 == 1) o = 0;
   //cerr << ans << '\n';  
  }
 }
 for(auto c : col_travs) { 
  if(!vis_col[c]) {
   vis_col[c] = 1; 
   int cc_size = dfs(c, false); 
   ans += cc_size - 1; 
   if(cc_size % 2 == 1) o = 0; 
  }
 }
 vector<ll>pw2(N + 1);
 pw2[0] = 1;  
 for(int i = 1; i < N + 1; i++) { 
  pw2[i] = (pw2[i - 1] * 2) % MOD; 
 }
 int num = ans - (o && sz(row_travs) == R && sz(col_travs) == C); 
 cout << pw2[num] << '\n'; 
 return 0; 
}
