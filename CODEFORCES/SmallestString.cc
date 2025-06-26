#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

const int64_t oo = 1e9; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<string>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 sort(a.begin(), a.end(), [&](string a, string b) {
  return a + b < b + a; 
 });
 string ret = ""; 
 for(int i = 0; i < N; i++) { ret += a[i]; }
 cout << ret << '\n';  
 return 0; 
} 