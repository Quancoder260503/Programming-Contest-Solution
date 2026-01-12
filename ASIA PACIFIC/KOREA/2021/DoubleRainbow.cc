#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
int main(void) {
  int N, K; 
  cin >> N >> K; 
  vector<int>a(N);
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  unordered_map<int, int>mp_in, mp_out; 
  for(int i = 0; i < N; i++) { 
   mp_out[a[i]]++; 
  }
  if(sz(mp_out) < K) { 
   cout << 0 << '\n'; 
   return 0; 
  }
  int ret = N + 1; 
  for(int i = 0, ptr = 0; i < N; i++) { 
   while(ptr < N && sz(mp_in) < K) { 
    mp_in[a[ptr]]++; 
    mp_out[a[ptr]]--; 
    if(mp_out[a[ptr]] == 0) { 
     mp_out.erase(a[ptr]); 
    }
    ptr++; 
   }
   if(sz(mp_in) == K && sz(mp_out) == K) {
   // cout << i << " " << ptr << '\n'; 
    ret = min(ret, ptr - i);
   }  
   mp_in[a[i]]--; 
   if(mp_in[a[i]] == 0) { 
    mp_in.erase(a[i]); 
   }
   mp_out[a[i]]++; 
  }
  cout << (ret == N + 1 ? 0 : ret) << '\n'; 
  return 0; 
}