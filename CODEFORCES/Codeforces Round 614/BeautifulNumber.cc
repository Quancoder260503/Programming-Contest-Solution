#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, T; 
  for(cin >> T; T--; ) { 
    cin >> N;
    vector<pair<int, int>>arr;
    for(int i = 0, x; i < N; i++) { 
      cin >> x; 
      arr.push_back({x, i}); 
    }
    sort(arr.begin(), arr.end()); 
    int mx = arr[0].second, mn = arr[0].second, space = 0;
    vector<int>ret = {1}; 
    for(int i = 1; i < N; i++) { 
      int pos = arr[i].second; 
      if(mn < pos && pos < mx) { 
        ret.push_back(space == 1); 
      }
      else if(mn - 1 == pos || pos == mx + 1) { 
        ret.push_back(space == 0); 
      }
      else { 
        ret.push_back(0); 
      }
      if(mn < pos && pos < mx) { 
        space--; 
      }
      if(pos > mx) { 
        space += pos - mx - 1; 
        mx = pos; 
      }
      if(pos < mn) { 
        space += mn - pos - 1; 
        mn = pos; 
      }
    }
    for(auto &x : ret) { cout << x; }
    cout << '\n'; 
  }
  return 0; 
}