#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e6; 

int main(void) { 
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int G, N, M; 
  cin >> G >> N >> M; 
  vector<int>a(N), b(M), coord; 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
    coord.push_back(a[i]); 
  }
  for(int i = 0; i < M; i++) { 
    cin >> b[i]; 
    coord.push_back(b[i]); 
  }
  sort(coord.begin(), coord.end()); 
  coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
  vector<int>visA(sz(coord)), visB(sz(coord)); 
  for(int i = 0; i < N; i++) { 
    int pos = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin(); 
    visA[pos] = true; 
  }
  for(int i = 0; i < M; i++) { 
    int pos = lower_bound(coord.begin(), coord.end(), b[i]) - coord.begin(); 
    visB[pos] = true; 
  }
  vector<vector<int>>dyn(sz(coord), vector<int>(2, -1)); 
  function<int(int, int)> memo = [&](int pos, int id) { 
    if(pos == sz(coord)) return 0; 
    int &ret = dyn[pos][id]; 
    if(ret != -1) return ret; 
    ret = oo;
    if((id == 0 && visA[pos]) || (id == 1 && visB[pos])) { 
      ret = min(ret, memo(pos + 1, id)); 
    } 
    if((id == 0 && !visA[pos]) || (id == 1 && !visB[pos])) { 
        ret = min(ret, 1 + memo(pos + 1, id ^ 1)); 
    } 
    return ret; 
  }; 
  cout << min(memo(0, 1), memo(0, 0)) << '\n'; 
  return 0; 
}