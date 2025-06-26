#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
 int N;
 cin >> N; 
 int ret = 0; 
 for(int i = 0, x; i < N; i++) {  
  cin >> x; 
  int ctr = 0; 
  for(int j = 2; j * j <= x; j++) { 
   while(x % j == 0) { ctr++; x = x / j; }
  } 
  if(x > 1) ctr++; 
  ret = ret ^ ctr; 
 }
 cout << (ret ? "Anna" : "Bruno") << '\n'; 
 return 0; 
}