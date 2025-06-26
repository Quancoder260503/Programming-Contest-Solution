#include <bits/stdc++.h> 

using namespace std; 

bitset<200005>dp; 

int main() { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N; 
 cin >> N; 
 vector<int>a(N);
 int cnt = 0, sum; 
 dp[0] = 1; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i];
  dp |= (dp << a[i]); 
  sum += a[i]; 
 }
 if(sum % 2 == 0 && dp[sum / 2]) { 
  pair<int, int>ret = {20, 0}; 
  for(int i = 0; i < N; i++) { 
   ret = min(ret, {__builtin_ctz(a[i]), i}); 
  } 
  cout << 1 << "\n" << ret.second + 1 << '\n'; 
 } else { 
  cout << 0 << '\n'; 
 } 
 return 0;
}