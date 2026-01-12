#include <bits/stdc++.h> 
#include <iostream>
 
using namespace std; 
 
int main() {
  int N; 
  cin >> N; 
  vector<array<int, 2>>arr(N); 
  for(int i = 0; i < N; i++) { 
   cin >> arr[i][0] >> arr[i][1]; 
  } 
  sort(arr.rbegin(), arr.rend()); 
  int64_t ans = 0; 
  for(int i = 0; i < N; i++) { 
   int j = i, max_so_far = arr[i][1]; 
   while(j < N && arr[i][0] == arr[j][0]) { 
    max_so_far = max(max_so_far, arr[j][1]); 
    j++; 
   } 
   ans += max_so_far; 
   i = j - 1;
  } 
  cout << ans << '\n'; 
  return 0;
}