#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, S, H;
  cin >> N >> S >> H; 
  multiset<int>ms; 
  for(int i = 0, x; i < N; i++) { 
    cin >> x; 
    ms.insert(x); 
  }
  int ret = S; 
  for(int i = 0; i < H; i++) { 
    auto it = ms.lower_bound(ret); 
    if(it != ms.begin()) { 
      it--; 
      ret += ceil(sqrt(*it)); 
      ms.erase(it); 
    }
  }
  cout << ret << '\n'; 
  return 0;
}