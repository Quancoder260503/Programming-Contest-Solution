#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

const int BASE = 37; 
const int mod = 1e9 + 7; 

vector<int64_t> getHash(const string &s) { 
  int N = sz(s); 
  vector<int64_t>ret(N + 1); 
  for(int i = 0; i < N; i++) { 
    ret[i + 1] = (ret[i] * BASE % mod + s[i] - 'a') % mod; 
  }
  return ret; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, Q, T; 
  cin >> T; 
  for(int iter = 0; iter < T; iter++) { 
    cin >> N; 
    string s; 
    vector<vector<int64_t>>hashCode; 
    for(int i = 0; i < N; i++) { 
      cin >> s; 
      hashCode.push_back(getHash(s)); 
    }
    cout << "Case " << iter + 1 << ":\n"; 
    cin >> Q; 
    for(int q = 0, u, v; q < Q; q++) { 
      cin >> u >> v; 
      --u, --v; 
      int lo = 0, hi = min(sz(hashCode[u]), sz(hashCode[v])) - 1; 
      while(lo < hi) { 
        int mid = (lo + hi + 1) / 2; 
        if(hashCode[u][mid] == hashCode[v][mid]) { 
          lo = mid; 
        }
        else { 
          hi = mid - 1; 
        }
      }
      cout << lo << '\n'; 
    } 
  }
  return 0; 
}