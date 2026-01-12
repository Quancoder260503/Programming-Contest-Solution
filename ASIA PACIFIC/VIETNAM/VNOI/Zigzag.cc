#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { 
   int n; 
   cin >> n; 
   map<int, map<int, int>>mp; 
   auto addRange = [&](int x, int y, int len) { 
    mp[x - y][y]++; 
    mp[x - y][y + len + 1]--; 
   }; 
   for(int i = 0, x, y, len, c; i < n; i++) { 
    cin >> x >> y >> len >> c; 
    addRange(x, y, len / 2); 
    addRange(x + (c == 0), y + (c == 1), len - (len / 2) - 1); 
   }
   int64_t ans = 0;
   for(auto &[_, gr] : mp) { 
    int64_t prev_pos = 0, sum = 0; 
    for(auto &[y, amt] : gr) { 
     ans += sum * (sum - 1) / 2 * (y - prev_pos); 
     sum += amt; 
     prev_pos = y;    
    }
   }
   cout << ans << '\n'; 
  }
  return 0; 
}
