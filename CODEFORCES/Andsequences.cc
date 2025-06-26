/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>

using namespace std; 

const int MOD = 1e9 + 7; 

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, T;
 for(cin >> T; T--; ) {
  cin >> N; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  } 
  int c = a[0]; 
  for(int i = 1; i < N; i++) { 
   c = c & a[i]; 
  } 
  int ctr = 0; 
  for(int i = 0; i < N; i++) { 
    ctr += (c == a[i]); 
  }
  int64_t ret = 1LL * ctr * (ctr - 1) % MOD;
  for(int i = 1; i < N - 1; i++) { 
    ret = ret % MOD * i % MOD; 
  } 
  cout << ret << '\n'; 
 }
 return 0;
}