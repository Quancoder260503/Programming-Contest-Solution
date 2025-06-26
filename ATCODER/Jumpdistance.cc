#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<vector<int>>a(4);
  for(int i = 0, x, y; i < N; i++) { 
   cin >> x >> y;
   if((x + y) % 2 == 0) { 
    a[0].push_back(x + y); 
    a[1].push_back(x - y); 
   } else { 
    a[2].push_back(x + y); 
    a[3].push_back(x - y); 
   }
  }
  int64_t ans = 0; 
  for(int i = 0; i < 4; i++) { 
   sort(a[i].begin(), a[i].end()); 
   for(int j = 0; j < sz(a[i]); j++) { 
    ans += 1LL * a[i][j] * (2 * j + 1 - sz(a[i])); 
   }
  }
  ans = ans / 2; 
  cout << ans << '\n'; 
  return 0; 
}
