#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 10000; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Prob, N, Q; 
  cin >> Q; 
  vector<int>ctr(maxf + 1); 
  iota(ctr.begin() + 1, ctr.end(), 0);
  ctr[1] = 2; 
  for(int i = 2; i <= maxf; i++) { 
    vector<int>vis(maxf + 1, false); 
    for(int j = 2; j * j <= i; j++) { 
      if(i % j == 0) { 
        int c = i / j; 
        for(int x = i + j; x <= maxf; x += j) if(!vis[x]) { 
          vis[x] = true; 
          ctr[x]--; 
        }
        for(int x = i + c; x <= maxf; x += c) if(!vis[x]) { 
          vis[x] = true; 
          ctr[x]--; 
        }
      }
    }
    for(int x = 2 * i; x <= maxf; x += i) if(!vis[x]) { 
      vis[x] = true; 
      ctr[x]--; 
    }
  } 
  for(int i = 1; i <= maxf; i++) { 
    ctr[i] += ctr[i - 1]; 
  }
  for(int iter = 0; iter < Q; iter++) { 
    cin >> Prob >> N;
    cout << Prob << " " << ctr[N] << '\n'; 
  }
  return 0; 
}
