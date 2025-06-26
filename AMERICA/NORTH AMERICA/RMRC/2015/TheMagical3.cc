#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int64_t N; 
  while(cin >> N && N) { 
    if(N == 2) { 
      cout << "no such base\n";
      continue; 
    }
    if(N == 3) {
      cout << 4 << '\n'; 
      continue; 
    }
    vector<int>cc; 
    N = N - 3; 
    for(int64_t i = 1; 1LL * i * i <= N; i++) { 
      if(N % i == 0) { 
        if(i     > 3) { cc.push_back(i); } 
        if(N / i > 3) { cc.push_back(N / i); } 
      }
    }
    sort(cc.begin(), cc.end()); 
    if(sz(cc) == 0) { 
      cout << "no such base\n"; 
    }
    else { 
      cout << cc[0] << '\n'; 
    }
  }
  return 0; 
}
/*
  N = a[k] * b ^ k + a[k - 1] * b ^ (k - 1) + ... + a[0],  (a[0] == 3);
  (N - 3) % == 0 (mod b);  
*/ 
