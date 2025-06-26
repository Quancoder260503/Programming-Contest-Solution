#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int oo = 1e9; 
 
class Bottle { 
 public :
  void solve() { 
  int N; 
  cin >> N; 
  N--; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  int ans = 1; 
  for(int i = 1; i < N; i++) { 
    if(a[i]) continue; 
    int j = i + 1; 
    while(j < N && a[i] == a[j]) j++; 
    if(j < N) { 
     ans = max(ans, 2);
    } else {
     ans = max(ans, j - i + 1);
    } 
    i = j - 1;
  }
  cout << ans << '\n'; 
  return;  
 } 
}; 
 
int main(void) { 
  Bottle task; 
  task.solve(); 
  return 0; 
}