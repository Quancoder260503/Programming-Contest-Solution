#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 2e9; 

pair<int, int> solve(vector<int>&a, vector<int>&b, int n) { 
 vector<int>suffix(n + 1); 
 vector<vector<int>>prefix(n, vector<int>(2, oo)); 
 for(int i = n - 1; i >= 0; i--) { 
  suffix[i] = abs(a[i] - b[i]); 
  suffix[i] = max(suffix[i], suffix[i + 1]); 
 }
 prefix[0][1] = 0; 
 prefix[0][0] = abs(a[0] - b[0]); 
 for(int i = 1; i < n; i++) {    
  prefix[i][0] = max(prefix[i - 1][0], abs(a[i] - b[i]));
  prefix[i][1] = min(prefix[i][1], max(prefix[i - 1][0], abs(b[i] - a[i - 1])));
  prefix[i][1] = min(prefix[i][1], max(prefix[i - 1][1], abs(b[i] - a[i - 1])));  
  //cout << prefix[i][1] << " " << abs(b[i] - a[i - 1]) << '\n'; 
 }
 int ret = 1e9, ans = 1e9;  
 for(int i = 1; i < n; i++) { 
  int curr = max(i ? prefix[i - 1][0] : 0, suffix[i + 1]); 
  if(curr < ret) { 
   ret = curr;
   ans = a[i];   
  } else if(curr == ret) { 
   ans = min(ans, a[i]); 
  }
  curr = max(prefix[i][1], suffix[i + 1]); 
  if(curr < ret) { 
    ret = curr;
    ans = a[i];   
   } else if(curr == ret) { 
    ans = min(ans, a[i]); 
   }
 }
 return {ret, ans}; 
}


int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int n; 
  cin >> n;
  vector<int>a(n), b(n);  
  for(int i = 0; i < n; i++) { 
   cin >> a[i]; 
  }
  for(int i = 0; i < n; i++) { 
   cin >> b[i]; 
  }
  sort(a.begin(), a.end()); 
  sort(b.begin(), b.end()); 
  auto ret = solve(a, b, n); 
  reverse(a.begin(), a.end()); 
  reverse(b.begin(), b.end());
  ret = min(ret, solve(a, b, n)); 
  cout << ret.second << '\n';  
  return 0; 
}