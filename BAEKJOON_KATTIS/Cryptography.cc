#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int MOD = 1e9 + 7; 

struct Fenwick { 
 vector<int>bit; 
 int N; 
 Fenwick(int n) { 
   N = n; 
   bit.resize(N + 1); 
   return; 
 }
 int sum(int pos) { 
   int ret = 0; 
   for(pos++; pos > 0; pos -= (pos & -pos)) { 
    ret += bit[pos]; 
   }
   return ret; 
 }
 void update(int pos, int val) { 
  for(pos++; pos < N; pos += (pos & -pos)) { 
   bit[pos] += val;  
  }  
  return; 
 }
}; 
 
class Crypt{ 
 public :
  void solve() { 
  int N; 
  cin >> N; 
  vector<int>a(N), coord;
  vector<int64_t>fact(N + 1, 1); 
  fact[0] = 1; 
  for(int i = 1; i <= N; i++) { 
   fact[i] = fact[i - 1] % MOD * i % MOD; 
  } 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
   coord.push_back(a[i]); 
  }
  sort(coord.begin(), coord.end()); 
  int64_t ans = 0; 
  Fenwick fenw(N + 7); 
  for(int i = 0; i < N; i++) { 
   a[i] = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin(); 
   int pos = fenw.sum(a[i]); 
   (ans += 1LL * (a[i] - pos) % MOD * fact[N - i - 1] % MOD) %= MOD; 
   fenw.update(a[i], 1); 
  }
  ans++; 
  cout << ans % MOD << '\n'; 
  return;  
 } 
}; 
 
int main(void) { 
  Crypt task; 
  task.solve(); 
  return 0; 
}