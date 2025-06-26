#include "bits/stdc++.h"

using namespace std;

const int oo = 1e9; 
const int maxf = 60001; 

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, R;
  cin >> N >> R;
  vector<int>a(N + 1), b(N + 1);  
  vector<pair<int, int>>pos, neg; 
  for(int i = 1; i <= N; i++) { 
    cin >> a[i] >> b[i]; 
    if(b[i] >= 0) { 
      pos.push_back({a[i], b[i]}); 
    }
    else { 
      a[i] = max(a[i], abs(b[i])); 
      neg.push_back({a[i],b[i]}); 
    }
  }
  sort(pos.begin(), pos.end()); 
  sort(neg.begin(), neg.end(), [&](pair<int, int>a, pair<int, int>b) { 
    return a.first + a.second > b.first + b.second;
  }); 
  int cc = 0; 
  for(int i = 0; i < sz(pos); i++) { 
    if(R >= pos[i].first) { 
      R += pos[i].second;
      cc++;  
    }
  }
  vector<vector<int>>dyn(sz(neg) + 1, vector<int>(R + 1, -oo)); 
  dyn[0][R] = cc; 
  for(int i = 0; i < sz(neg); i++) { 
    for(int j = 0; j <= R; j++) { 
      dyn[i + 1][j] = max(dyn[i][j], dyn[i + 1][j]); 
      if(j >= neg[i].first && j + neg[i].second >= 0) { 
        dyn[i + 1][j + neg[i].second] = max(dyn[i + 1][j + neg[i].second], dyn[i][j] + 1);
      } 
    }
  }
  int ret = -oo; 
  for(int i = 0; i <= R; i++) {
    ret = max(ret, dyn[sz(neg)][i]); 
  }
  cout << ret << '\n'; 
  return 0;
}