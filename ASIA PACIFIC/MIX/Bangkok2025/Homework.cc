#include <vector> 
#include <iostream> 

using namespace std; 

const int oo = 1e8; 
const int N = 1e5 + 20; 
const int M = 700; 

struct Fenwick { 
 vector<pair<int, int>>bit;
 int n;  
 Fenwick(int _n) : n(_n), bit(_n, {-oo, -1}) {}; 
 void update(int pos, int v, int ind) { 
  for(pos++; pos < n; pos += pos & -pos) { 
   bit[pos] = max(bit[pos], {v, ind}); 
  }
 }
 pair<int, int> query(int pos) { 
  pair<int, int> ret = {-oo, -1} ; 
  for(pos++; pos > 0; pos -= pos & -pos) { 
   ret = max(ret, bit[pos]); 
  }
  return ret; 
 }
 void reset() { 
  fill(bit.begin(), bit.end(), make_pair(-oo, -1)); 
 }
}; 

int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0);
 int n; 
 cin >> n;
 vector<int>a(n + 1); 
 for(int i = 1; i <= n; i++) { 
  cin >> a[i]; 
 }
 vector<vector<int>>dp(n + 2, vector<int>(M + 1, oo)); 
 vector<vector<int>>par(n + 2, vector<int>(M + 1, -1)); 
 for(int i = 1; i <= n; i++) { 
  dp[i][1] = 0; 
 }

 Fenwick fenw(N + 2); 
 pair<int, int> ret = {1, 1}; 
 for(int j = 1; j < M; j++) { 
  for(int i = j; i <= n; i++) { 
   auto prev_opt = fenw.query(a[i] - 1);
   if(prev_opt.first != -oo) { 
  // cerr << dp[i][j + 1] << " " << a[i] - prev_opt.first << '\n'; 
    if(dp[i][j + 1] > a[i] - prev_opt.first) { 
      dp[i][j + 1] = a[i] - prev_opt.first; 
      par[i][j + 1] = prev_opt.second;   
    } 
   }
   if(dp[i][j] < oo) {  
    fenw.update(a[i] + dp[i][j], a[i], i);    
   } 
   if(dp[i][j + 1] < oo) { 
    if(ret.first < j + 1 && prev_opt.second != -1) { 
     ret.first = j + 1;
     ret.second = i;  
    }
   }
  }
  fenw.reset(); 
 } 
 pair<int, int>curr = {ret.second, ret.first}; 
 cout << curr.second << '\n';
 vector<int>ans; 
 while(curr.first != -1) { 
  ans.push_back(curr.first); 
  int u = par[curr.first][curr.second]; 
 // cout << u << " " << curr.first << " " << curr.second << '\n';
  curr.second--; 
  curr.first = u; 
 }
 // cout << curr.second << '\n';
 reverse(ans.begin(), ans.end()); 
 for(auto &x : ans) cout << x << " "; 
 cout << '\n'; 
 return 0; 
}