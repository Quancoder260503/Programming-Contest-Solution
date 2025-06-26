#include "bits/stdc++.h"
 
using namespace std;
 
const int LOG = 32; 
 
unordered_map<int, int>dp; 
 
int grundy(int mask) { 
 if(mask == 0) return 0; 
 if(dp.count(mask)) return dp[mask]; 
 set<int>ms; 
 for(int i = 0; i < LOG; i++) { 
  if(mask >> i) { 
   int next_mask = (mask >> (i + 1)) | (mask & ((1 << i) - 1)); 
   ms.insert(grundy(next_mask)); 
  }
 }
 int mex = 0; 
 while(ms.count(mex)) mex++; 
 return dp[mask] = mex; 
} 
 
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<int>a(N);
  set<int>primes;  
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
   int x = a[i]; 
   for(int j = 2; j * j <= x; j++) { 
    if(x % j == 0) { 
     primes.insert(j); 
     while(x % j == 0) { x = x / j; }
    }
   }
   if(x > 1) { 
    primes.insert(x); 
   }
  } 
  int ret = 0; 
  for(auto &p : primes) { 
   int mask = 0; 
   for(int j = 0; j < N; j++) { 
    int x = a[j], cnt = 0; 
    while(x % p == 0) { 
     cnt++; 
     x = x / p; 
    }
    if(cnt == 0) continue; 
    mask |= 1 << (cnt - 1); 
   }
   ret = ret ^ grundy(mask); 
  }
  cout << (!ret ? "Arpa" : "Mojtaba") << '\n'; 
  return 0;
}