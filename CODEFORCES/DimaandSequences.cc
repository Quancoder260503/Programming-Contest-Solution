#include <bits/stdc++.h>
 
using namespace std; 
 
#define sz(x) int(x.size())
 
int main() { 
 int N; 
 cin >> N; 
 vector<int>a(N), b(N); 
 unordered_map<int, vector<int>>mp; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  mp[a[i]].push_back(i % N); 
 } 
 for(int i = 0; i < N; i++) { 
  cin >> b[i]; 
  mp[b[i]].push_back(i % N); 
 } 
 int MOD; 
 cin >> MOD; 
 vector<int64_t>fact(2 * N + 2); 
 vector<int64_t>pw2(2 * N + 2);
 fact[0] = 1; 
 for(int i = 1; i < sz(fact); i++) {
  int num = i, cnt = 0; 
  while(num % 2 == 0) { num = num / 2; cnt++; }
  pw2[i] = pw2[i - 1] + cnt; 
  fact[i] = 1LL * fact[i - 1] * num % MOD; 
 }
 int64_t ret = 1, acc = 0; 
 for(auto [_, x] : mp) { 
  ret = ret % MOD * fact[sz(x)] % MOD;
  acc += pw2[sz(x)]; 
 } 
 for(int i = 0; i < N; i++) { 
  if(a[i] == b[i]) { 
    acc--; 
  } 
 } 
 for(int i = 0; i < acc; i++) { 
  ret = ret * 2 % MOD; 
 }
 cout << ret << '\n'; 
 return 0;
}