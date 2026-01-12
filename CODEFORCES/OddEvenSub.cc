#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <assert.h> 
#include <numeric>
#include <stack>
#include <vector>

using namespace std; 

#define sz(x) int(x.size())
#define ll long long 

const int LOG = 22; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, k; 
  cin >> n >> k; 
  vector<int>a(n);
  for(auto &x : a) cin >> x; 
  auto check = [&](int curr, int x) { 
   int ans = 0; 
   for(int i = 0; i < n; i++) { 
    if(curr) { 
     ans++; 
     curr = curr ^ 1; 
    } else { 
     if(a[i] <= x) { 
      ans++; 
      curr = curr ^ 1;   
     }
    }
   }
   return ans >= k; 
  }; 
  int lo = 0, hi = 1e9; 
  while(lo < hi) { 
   int mid = (lo + hi) / 2;
   if(check(0, mid) || check(1, mid)) hi = mid; 
   else lo = mid + 1;    
  }
  cout << lo << '\n'; 
  return 0;
}