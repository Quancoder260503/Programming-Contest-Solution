#include "bits/stdc++.h"

using namespace std;

const int maxf = 5e5 + 10; 
const int mod = 998244353; 

int N, K, M;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> K >> M; 
  vector<array<int, 3>>q(M);
  for(int i = 0; i < M; i++) { 
    for(int j = 0; j < 3; j++) { 
      cin >> q[i][j]; 
    }
  }
  vector<int64_t> ways(N + 1);  
  vector<int>isOne(N + 1), nearestZero(N + 1);  
  int64_t ret = 1;
  for(int pos = K - 1; pos >= 0; pos--) {
    fill(ways.begin(), ways.end(), 0); 
    fill(isOne.begin(), isOne.end(), 0); 
    fill(nearestZero.begin(), nearestZero.end(), 0); 
    for(int i = 0; i < M; i++) { 
      int l = q[i][0], r = q[i][1], x = q[i][2];
      if((x >> pos) & 1) { 
        isOne[l]++; 
        isOne[r + 1]--; 
      }
      else { 
        nearestZero[r] = max(nearestZero[r], l); 
      }
    }
    for(int i = 1; i <= N; i++) { 
      isOne[i] += isOne[i - 1]; 
    }
    int64_t nums = 1;
    ways[0] = 1; 
    for(int i = 1, ptr = 0; i <= N; i++) { 
      if(!isOne[i]) { 
        ways[i] = nums; 
        nums = nums * 2 % mod; 
      }
      while(ptr < nearestZero[i]) { 
        (nums += mod - ways[ptr]) %= mod;
        ptr++; 
      }
    }
    ret = ret % mod * nums % mod; 
  }
  cout << ret << '\n'; 
  return 0; 
}