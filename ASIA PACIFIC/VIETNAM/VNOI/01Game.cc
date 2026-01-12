#include "bits/stdc++.h"

using namespace std; 


void solve() { 
  int k; 
  string s; 
  cin >> k >> s;
  int n = s.size();
  vector<int>dp(n + 1, -1); 
  function<int(int)>memo = [&](int num) { 
   if(num < k)  return 0; 
   if(num == k) return 1; 
   int &ret = dp[num];
   if(ret != -1) return ret; 
   unordered_set<int>ms; 
   for(int j = 1; j + k <= num; j++) { 
    int c = (memo(j - 1) ^ memo(num - j - k + 1)); 
   // cout << c << " " << j << " " << j + k - 1 << '\n'; 
    ms.insert(c); 
   }
   ret = 0; 
   while(ms.count(ret)) ret++; 
   return ret; 
  };
 // for(int i = 0; i <= n; i++) cout << i << " " << memo(i) << '\n'; 
  int grundy = 0; 
  for(int i = 0; i < n; i++) { 
   if(s[i] == '1') { 
    int cnt_ones = 0, ptr = i; 
    while(ptr < n && s[ptr] == '1') ptr++; 
    cnt_ones = ptr - i;
    //cout << cnt_ones << '\n'; 
    grundy = grundy ^ memo(cnt_ones); 
    i = ptr - 1; 
   } 
  }
  cout << (grundy ? 1 : 2) << '\n'; 
  return;    
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int C; 
  for(cin >> C; C--; ) solve(); 
  return 0;
}
