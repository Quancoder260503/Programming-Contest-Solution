#include "bits/stdc++.h"

using namespace std;

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N; 
 cin >> N; 
 vector<array<int, 3>>arr(N); 
 for(int i = 0; i < N; i++) { 
  cin >> arr[i][0] >> arr[i][1] >> arr[i][2]; 
 } 
 sort(arr.begin(), arr.end()); 
 vector<int>dp(N); 
 for(int i = 0; i < N; i++) { 
  for(int j = 0; j < i; j++) { 
   if(arr[i][1] >= arr[j][1]) { 
    dp[i] = max(dp[i], dp[j]); 
   }
  }
  dp[i] += arr[i][2]; 
 }
 cout << *max_element(dp.begin(), dp.end()) << '\n'; 
 return 0; 
}

