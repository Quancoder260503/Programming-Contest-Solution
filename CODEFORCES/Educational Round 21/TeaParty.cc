#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, W; 
  cin >> N >> W; 
  vector<pair<int, int>>arr;
  vector<int>b(N); 
  int sum = 0, tot = 0; 
  for(int i = 0, x; i < N; i++) { 
    cin >> b[i]; 
    tot += b[i]; 
    sum += (b[i] + 1) / 2; 
    arr.push_back({b[i], i}); 
  }
  sort(arr.rbegin(), arr.rend()); 
  if(sum > W || tot < W) { 
    cout << -1 << '\n'; 
    return 0; 
  }
  vector<int>ret(N); 
  for(auto [x, ind] : arr) { 
    ret[ind] = (x + 1) / 2; 
  }
  W = W - sum; 
  for(; W > 0; ) { 
    for(int i = 0; i < arr.size(); i++) { 
      if(W > 0 && ret[arr[i].second] < b[arr[i].second]) { 
        W--; 
        ret[arr[i].second]++; 
      }
      else if(W == 0) { 
        break; 
      }
    }
  } 
  for(int i = 0; i < N; i++) { 
    cout << ret[i] << " "; 
  }
  cout << '\n'; 
  return 0;
}

    
