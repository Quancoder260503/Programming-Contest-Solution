#include "bits/stdc++.h"

using namespace std; 

const int maxn = 1e6 + 2; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<int>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 int j; 
 for(j = 0; j + 1 < N; j++) { 
  if(a[j] > a[j + 1]) { 
   break; 
  }
 } 
 while(j > 0 && a[j] == a[j - 1]) { 
  j--; 
 }
 int left = j; 
 while(j + 1 < N && a[j] >= a[j + 1]) { 
  j++; 
 }
 int right = j; 
 reverse(a.begin() + left, a.begin() + right + 1); 
// cout << left << " " << right << '\n'; 
 cout << (is_sorted(a.begin(), a.end()) ? "Yes" : "No") << '\n';  
 return 0; 
}