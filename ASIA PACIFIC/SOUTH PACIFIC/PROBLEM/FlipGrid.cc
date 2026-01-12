#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e9; 

int to_num(const string &c) {
 int curr = 0; 
 for(int i = 0; i < 16; i++) { 
  curr += (1 << i) * (c[i] - '0'); 
 }
 return curr; 
} 

string to_str(int s) { 
  string ret = ""; 
  for(int i = 0; i < 16; i++) { 
   ret = ret + (s >> i & 1 ? '1' : '0'); 
  }
  return ret; 
} 

vector<vector<char>>to_grid(const string s) { 
 vector<vector<char>>ret(4, vector<char>(4)); 
 for(int i = 0; i < 16; i++) { 
  ret[i / 4][i % 4] = s[i]; 
 }
 return ret; 
}

int flip(vector<vector<char>>curr) { 
  vector<vector<char>>ret(4, vector<char>(4));  
  for(int i = 0; i < 4; i++) { 
   for(int j = 0; j < 4; j++) { 
    ret[j][3 - i] = curr[i][j]; 
   }
  }
  int ans = 0; 
  for(int i = 0; i < 4; i++) { 
   for(int j = 0; j < 4; j++) { 
    ans += (ret[i][j] == '1') * (1 << (i * 4 + j));
   }
  }
  return ans;  
}

int rev_row(vector<vector<char>>curr, int row) { 
 vector<vector<char>>ret = curr; 
 for(int i = 0; i < 4; i++) { 
  ret[row][i] = (ret[row][i] == '1' ? '0' : '1'); 
 }
 int ans = 0; 
 for(int i = 0; i < 4; i++) { 
  for(int j = 0; j < 4; j++) { 
   ans += (ret[i][j] == '1') * (1 << (i * 4 + j));
  }
 }
 return ans; 
}

int rev_col(vector<vector<char>>curr, int col) { 
 vector<vector<char>>ret = curr; 
 for(int i = 0; i < 4; i++) { 
  ret[i][col] = (ret[i][col] == '1' ? '0' : '1'); 
 }
 int ans = 0; 
 for(int i = 0; i < 4; i++) { 
  for(int j = 0; j < 4; j++) { 
   ans += (ret[i][j] == '1') * (1 << (i * 4 + j));
  }
 }
 return ans; 
}

int main(void) { 
 string st, en; 
 string s; 

 for(int i = 0; i < 4; i++) { 
  cin >> s; 
  st += s; 
 }
 for(int i = 0; i < 4; i++) { 
  cin >> s; 
  en += s; 
 }
 vector<int>dp(1 << 16, oo); 
 using T = pair<int, int>; 
 priority_queue<T, vector<T>, greater<T>>pq; 
 int start = to_num(st); 
 int end_  = to_num(en); 
 dp[start] = 0; 
 pq.push({dp[start], start}); 
 while(pq.size()) { 
  auto [d, u] = pq.top(); 
  pq.pop(); 
  if(dp[u] != d) continue;  
  auto curr_grid = to_grid(to_str(u)); 
  int flip_grid = flip(curr_grid); 
  if(dp[flip_grid] > dp[u] + 1) { 
   dp[flip_grid] = dp[u] + 1; 
   pq.push({dp[flip_grid], flip_grid}); 
  }
  for(int row = 0; row < 4; row++) { 
   int nxt_grid = rev_row(curr_grid, row); 
   if(dp[nxt_grid] > dp[u] + 1) { 
    dp[nxt_grid] = dp[u] + 1; 
    pq.push({dp[nxt_grid], nxt_grid}); 
   }
  }
  for(int col = 0; col < 4; col++) { 
   int nxt_grid = rev_col(curr_grid, col); 
   if(dp[nxt_grid] > dp[u] + 1) { 
    dp[nxt_grid] = dp[u] + 1; 
    pq.push({dp[nxt_grid], nxt_grid}); 
   }
  }
 }
 cout << (dp[end_] == oo ? -1 : dp[end_]) << '\n'; 
 return 0; 
}