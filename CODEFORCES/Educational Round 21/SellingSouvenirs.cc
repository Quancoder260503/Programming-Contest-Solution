#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())

const int oo = 1e8; 
 
int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, W; 
  cin >> N >> W;
  vector<vector<int64_t>>ctr(3);
  for(int i = 0, w, c; i < N; i++) { 
    cin >> w >> c; 
    ctr[w - 1].push_back(c);
  }
  for(int i = 0; i < sz(ctr); i++) { 
    sort(ctr[i].begin(), ctr[i].end()); 
    ctr[i].push_back(0); 
    reverse(ctr[i].begin(), ctr[i].end()); 
    for(int j = 1; j < sz(ctr[i]); j++) { 
      ctr[i][j] += ctr[i][j - 1]; 
    }
  }
  int64_t ret = 0; 
  for(int z = 0; z < sz(ctr[2]); z++) { 
    int remW = W - 3 * z;  
    if(remW < 0) continue; 
    auto cost = [&](int y) -> int64_t { 
       int x = remW - 2 * y; 
       if(x < 0 || y < 0) return -oo; 
       int64_t ret = ctr[2][z]; 
       ret += ctr[1][min(sz(ctr[1]) - 1, y)]; 
       ret += ctr[0][min(sz(ctr[0]) - 1, x)]; 
       return ret; 
    }; 
    int lo = -1, hi = sz(ctr[1]) + 1; 
    while(hi - lo > 1) { 
      int mid = (hi + lo) / 2;
      if(cost(mid) < cost(mid + 1)) { 
        lo = mid; 
      }
      else { 
        hi = mid; 
      }
    }
    ret = max(ret, cost(hi));  
  }
  cout << ret << '\n'; 
  return 0; 
}
/*
 Let x, y, z be the number of balls with weight 1, 2, 3.
    x + 2 * y + 3 * z <= M
    maximize P[1][x] + P[2][y] + P[3][z] 
*/