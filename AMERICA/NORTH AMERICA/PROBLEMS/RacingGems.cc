#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long
#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, R, W, H; 
  cin >> N >> R >> W >> H; 
  vector<pair<int64_t, int64_t>>a; 
  for(int i = 0, x, y; i < N; i++) { 
    cin >> x >> y; 
    a.push_back({1LL * x * R + 1LL * y, 1LL * y - 1LL * x * R}); 
  }
  sort(a.begin(), a.end()); 
  vector<int64_t>best; 
  for(int i = 0; i < N; i++) { 
    int pos = upper_bound(best.begin(), best.end(), a[i].second) - best.begin(); 
    if(pos == sz(best)) { 
      best.push_back(a[i].second); 
    }
    else { 
      best[pos] = a[i].second; 
    }
  }
  cout << sz(best) << '\n'; 
  return 0; 
}

