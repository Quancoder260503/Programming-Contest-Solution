#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

void solve() { 
  int N, Q; 
  cin >> N >> Q; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }  
  vector<int>prefix(N + 1);
  vector<int>coord{0}; 
  for(int i = 0; i < N; i++) { 
   prefix[i + 1] = prefix[i] ^ a[i]; 
   coord.push_back(prefix[i + 1]); 
  }
  sort(coord.begin(), coord.end()); 
  coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
  int M = sz(coord); 
  vector<vector<int>>vec(M); 
  for(int i = 0; i <= N; i++) { 
   prefix[i] = lower_bound(coord.begin(), coord.end(), prefix[i]) - coord.begin(); 
   vec[prefix[i]].push_back(i); 
  }
  for(int i = 0, L, R; i < Q; i++) { 
   cin >> L >> R; 
   if(prefix[R] == prefix[L - 1]) { 
    cout << "YES\n"; 
   } else { 
    int posL = *(--lower_bound(vec[prefix[L - 1]].begin(), vec[prefix[L - 1]].end(), R)); 
    int posR = *(lower_bound(vec[prefix[R]].begin(), vec[prefix[R]].end(), L)); 
    cout << (posL > posR ? "YES" : "NO") << '\n'; 
   }
  }
  cout << '\n'; 
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { solve(); }
  return 0; 
}
