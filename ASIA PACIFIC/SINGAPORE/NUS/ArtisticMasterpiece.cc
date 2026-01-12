#include "bits/stdc++.h"
 
 
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
 
using namespace std;
 
const int LOG = 250;  
const int oo = 1e9; 
 
int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n;
 double r;  
 string s; 
 cin >> n >> r >> s;
 map<int, vector<pair<int, int>>>mp; 
 pair<int, int>curr = {0, 0};
 s = " " + s;  
 for(int i = 0; i <= n; i++) {   
  if(s[i] == 'L') { 
   curr.first--;  
  }
  if(s[i] == 'R') { 
   curr.first++; 
  }
  if(s[i] == 'U') { 
   curr.second--; 
  }
  if(s[i] == 'D') { 
   curr.second++; 
  }
  for(int cand_y = 0; cand_y <= LOG; cand_y++) {
   double dy = pow(cand_y, 4); 
   if(dy <= r) { 
    int dist_x = int(sqrt(r - dy)); 
  //  cout << curr.first - dist_x << " " << curr.first + dist_x << " " << i << '\n'; 
    mp[curr.second + cand_y].push_back({curr.first - dist_x, curr.first + dist_x + 1}); 
    mp[curr.second - cand_y].push_back({curr.first - dist_x, curr.first + dist_x + 1}); 
   }
  }
 }
 int64_t ret = 0;
 for(auto &[y, coord] : mp) { 
  int prev = -oo; 
  sort(coord.begin(), coord.end()); 
  for(auto &[l, r] : coord) { 
    prev = max(prev, l); 
    if(prev < r) { 
      ret += r - prev; 
      prev = r; 
    }
  } 
 }
 cout << ret << '\n'; 
 return 0;
}
