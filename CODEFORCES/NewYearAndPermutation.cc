#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, MOD; 
 cin >> n >> MOD; 
 vector<int64_t>fact(n + 2), f(n + 2); 
 fact[0] = 1; 
 for(int i = 1; i < sz(fact); i++) { 
  fact[i] = fact[i - 1] * i % MOD; 
 } 
 for(int i = 0; i <= n; i++) { 
  (f[i] = ((i ? f[i - 1] : 0) + fact[i + 1] % MOD * fact[n - i] % MOD)) %= MOD; 
 }
 int64_t ret = 0; 
 for(int i = 1; i <= n; i++) { 
  (ret += f[i - 1]) %= MOD; 
 } 
 cout << ret << '\n'; 
 return 0; 
}