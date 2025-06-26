#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

class Humanoid { 
  public:   
   vector<int>arr; 
   int rec(int pos, int64_t h, int a, int b) { 
    if(pos == sz(arr)) return 0; 
    if(h > arr[pos]) { 
      return 1 + rec(pos + 1, h + arr[pos] / 2, a, b); 
    }
    int ret = 0; 
    if(a) ret = max(ret, 2 * h > arr[pos] ? 1 + rec(pos + 1, 2 * h + arr[pos] / 2, a - 1, b) : rec(pos, 2 * h, a - 1, b));
    if(b) ret = max(ret, 3 * h > arr[pos] ? 1 + rec(pos + 1, 3 * h + arr[pos] / 2, a, b - 1) : rec(pos, 3 * h, a, b - 1)); 
    return ret; 
   }
   void solve() { 
    int N, H; 
    cin >> N >> H; 
    arr.resize(N); 
    for(int i = 0; i < N; i++) { 
     cin >> arr[i]; 
    }
    sort(arr.begin(), arr.end()); 
    cout << rec(0, H, 2, 1) << '\n'; 
    return; 
   }
};


int main(void) {  
 Humanoid human; 
 int T; 
 for(cin >> T; T--; ) { 
  human.solve(); 
 } 
 return 0; 
}