#include "bits/stdc++.h"

using namespace std;  

const int MOD = 1e9 + 7; 

#define ll long long 
#define sz(x) int(x.size()) 


int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n; 
 cin >> n; 
 int min_green = INT_MAX; 
 vector<pair<int, char>>col(n);
 for(int i = 0; i < n; i++) { 
  cin >> col[i].first >> col[i].second; 
  if(col[i].second == 'G') { 
   min_green = min(min_green, col[i].first); 
  }
 }
 int res = 0; 
 for(int i = 0; i < n; i++) { 
  if(col[i].second == 'B' && col[i].first < min_green) { 
   res = max(res, col[i].first); 
  }
 }
 cout << res << '\n'; 
 return 0; 
}