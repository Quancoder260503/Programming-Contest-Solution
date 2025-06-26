#include <bits/stdc++.h> 

using namespace std; 

int main() {
 int N; 
 cin >> N; 
 int ret = 0; 
 vector<int>a(N);
 int sum = 0; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  sum ^= a[i]; 
 } 
 for(int i = 0; i < N; i++) { 
  if(a[i] > (sum ^ a[i])) { 
   ret++; 
  } 
 } 
 cout << ret << '\n'; 
 return 0; 
}