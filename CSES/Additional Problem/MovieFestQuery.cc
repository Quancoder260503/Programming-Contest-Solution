#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 5e5 + 10; 
const int LOG  = 22; 
const int M = 1e6 + 2; 

int N, Q, _nxt[M][LOG]; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> Q;  
  vector<pair<int, int>>movies(N); 
  memset(_nxt, -1, sizeof(_nxt)); 
  for(int i = 0; i < N; i++) { 
    cin >> movies[i].first >> movies[i].second; 
  } 
  sort(movies.begin(), movies.end());
  for(int i = M - 1, j = int(1e9); i >= 0; i--) { 
    while(sz(movies) && movies.back().first >= i) { 
      j = min(j, movies.back().second); 
      movies.pop_back();
    }
    _nxt[i][0] = j; 
  }
  for(int i = 1; i < LOG; i++) { 
    for(int j = 0; j < M; j++) { 
      if(_nxt[j][i - 1] == -1 || _nxt[j][i - 1] >= M) continue; 
      _nxt[j][i] = _nxt[_nxt[j][i - 1]][i - 1];
    }
  }
  for(int iter = 0, a, b; iter < Q; iter++) { 
    cin >> a >> b;
    int ret = 0; 
    for(int k = LOG - 1; k >= 0; k--) { 
      if(_nxt[a][k] != -1 && _nxt[a][k] <= b) { 
        ret += (1 << k); 
        a = _nxt[a][k]; 
      }
    }
    cout << ret << '\n'; 
  }
  return 0; 
}



