#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int oo = 1e9; 
const int K = 102; 
 
class ExchangeGems { 
 public :
  void solve() { 
  int N; 
  cin >> N; 
  vector<int>a(N + K + 1), b(N + K + 1); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i];
  }
  for(int i = 0; i < N; i++) { 
    cin >> b[i]; 
  }
  for(int i = 0; i < N + K; i++) { 
    a[i + 1] += a[i] / 2; 
    a[i] %= 2; 
  }
  for(int i = 0; i < N + K; i++) { 
    b[i + 1] += b[i] / 2; 
    b[i] %= 2; 
  }
  for(int i = N + K; i >= 0; i--) { 
   if(a[i] > b[i]) { 
    cout << "YES\n"; 
    return; 
   } else if(a[i] < b[i]) { 
    cout << "NO\n"; 
    return; 
   }
  }
  cout << "YES" << '\n'; 
  return;  
 } 
}; 
 
int main(void) { 
  ExchangeGems task; 
  int T; 
  cin >> T; 
  while(T--) { 
   task.solve(); 
  } 
  return 0; 
}
