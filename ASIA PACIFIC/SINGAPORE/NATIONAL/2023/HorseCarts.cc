#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M;
  cin >> N >> M; 
  vector<pair<int, int>>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i].second >> a[i].first; 
  }
  sort(a.rbegin(), a.rend()); 
  multiset<int>ms; 
  for(int i = 0, x; i < M; i++) { 
    cin >> x; 
    ms.insert(x); 
  }
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) { 
    if(sz(ms) == 0) break;
    auto it = ms.lower_bound(a[i].second); 
    if(it == ms.end()) continue; 
    ret += a[i].first; 
    ms.erase(it); 
  }
  cout << ret << '\n'; 
  return 0;
}