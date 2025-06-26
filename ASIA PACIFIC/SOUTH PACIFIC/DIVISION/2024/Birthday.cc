#include <bits/stdc++.h> 

using namespace std; 

int main() {
  int64_t x; 
  cin >> x; 
  int ret = 10000; 
  for(int base = 2; base <= 10; base++) { 
   int64_t num = x; 
   int cnt = 0; 
   while(num > 0) { 
    cnt += (num % base);
    num = num / base; 
   }
   ret = min(ret, cnt); 
  } 
  cout << ret << '\n'; 
  return 0;
}