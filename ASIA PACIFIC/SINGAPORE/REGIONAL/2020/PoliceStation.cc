#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int oo = 1e9; 
 
class Police { 
 public :
  void solve() { 
  int N; 
  cin >> N; 
  vector<int>x(N), y(N); 
  for(int i = 0; i < N; i++) { 
   cin >> x[i] >> y[i]; 
  }
  sort(x.begin(), x.end()); 
  sort(y.begin(), y.end()); 
  cout << (x[N - 1] - x[0] + 1) / 2 << " " << (y[N - 1] - y[0] + 1) / 2 << '\n'; 
  return;  
 } 
}; 
 
int main(void) { 
  Police task; 
  task.solve(); 
  return 0; 
}