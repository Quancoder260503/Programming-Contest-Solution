#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 10; 
const int oo = 1e8; 

int N, a[maxf], opt[maxf], dyn[maxf]; 

void doit(void) { 
  cin >> N; 
  for(int i = 1; i <= N; i++) { 
    opt[i] = -oo;
    dyn[i] = 0; 
  }
  for(int i = 1; i <= N; i++) { 
    cin >> a[i]; 
  }
  int ret = 0;
  for(int i = 1; i <= N; i++) { 
    dyn[i] = max(dyn[i - 1], i + 1 + opt[a[i]]); 
    opt[a[i]] = max(opt[a[i]], dyn[i - 1] - i); 
    ret = max(ret, dyn[i]); 
  }
  cout << ret << '\n'; 
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T; T--) { 
    doit(); 
  }
  return 0; 
}