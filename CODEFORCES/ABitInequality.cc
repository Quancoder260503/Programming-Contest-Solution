#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

void solve() {
 int N; 
 cin >> N; 
 vector<int>a(N + 1), prefix(N + 1), suffix(N + 1); 
 for(int i = 1; i <= N; i++) { 
  cin >> a[i]; 
  prefix[i] = a[i] ^ prefix[i - 1]; 
 } 
 vector<vector<int>>c(31, vector<int>(2));
 vector<vector<vector<int>>>dp1(N + 1, vector<vector<int>>(31, vector<int>(2)));  
 vector<vector<vector<int>>>dp2(N + 1, vector<vector<int>>(31, vector<int>(2)));  
 for(int i = 0; i < sz(c); i++) { 
  c[i][0]++; 
 }
 for(int i = 1; i <= N; i++) { 
  for(int j = 0; j < sz(c); j++) { 
   if(prefix[i] & (1 << j)) { 
    dp1[i][j][0] += c[j][1]; 
    dp1[i][j][1] += c[j][0]; 
   } else { 
    dp1[i][j][0] += c[j][0]; 
    dp1[i][j][1] += c[j][1]; 
   }
  }
  for(int j = 0; j < sz(c); j++) { 
   if(prefix[i] & (1 << j)) { 
    c[j][1]++; 
   } else { 
    c[j][0]++; 
   }
  }
 }
 for(int i = 0; i < 31; i++) { 
  c[i][0] = c[i][1] = 0; 
 }
 for(int i = 0; i < sz(c); i++) { 
  c[i][0]++; 
 }
 for(int i = N; i > 0; i--) { 
 if(i == N) suffix[i] = a[i]; 
 else suffix[i] = suffix[i + 1] ^ a[i];
 }
 for(int i = N; i > 0; i--) {  
  for(int j = 0; j < sz(c); j++) { 
   if(suffix[i] & (1 << j)) { 
    dp2[i][j][0] += c[j][1]; 
    dp2[i][j][1] += c[j][0]; 
   } else { 
    dp2[i][j][0] += c[j][0]; 
    dp2[i][j][1] += c[j][1]; 
   }
  }
  for(int j = 0; j < sz(c); j++) { 
   if(suffix[i] & (1 << j)) { 
    c[j][1]++; 
   } else { 
    c[j][0]++; 
   }
  }
 }
 int64_t ret = 0; 
 for(int i = 1; i <= N; i++) { 
  for(int j = 30; j >= 0; j--) { 
   if(a[i] & (1 << j)) { 
    ret += 1LL * dp1[i][j][1] * dp2[i][j][0]; 
    ret += 1LL * dp1[i][j][0] * dp2[i][j][1]; 
    break; 
   }
  } 
 } 
 cout << ret << '\n'; 
 return;    
}

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 for(cin >> T; T--; ) { solve(); }
 return 0;
}

/**
 * prefix[x - 1]  ^ prefix[z] ^ a[y] > prefix[x - 1] ^ prefix[z] ^ a[y]
 * To make sure that the sum of xor is greater, say x ^ y > x 
 * then let a be the highest 1 of x, b be the highest 1 of y
 * b > a  : always larger 
 * b == a : always smaller 
 * b < a  : if the b-th bit of x is 1 -> smaller otherwise larger 
 */ 