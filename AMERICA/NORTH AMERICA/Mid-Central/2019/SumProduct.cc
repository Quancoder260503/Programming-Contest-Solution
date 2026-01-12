#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxn = 1e6 + 2; 
int64_t suffix[maxn]; 
int one_pos[maxn]; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n;
 cin >> n; 
 vector<int>a(n); 
 for(int i = 0; i < n; i++) { 
  cin >> a[i]; 
 }
 for(int i = n - 1; i >= 0; i--) { 
  suffix[i] = suffix[i + 1] + a[i]; 
 }
 memset(one_pos, -1, sizeof one_pos); 
 for(int i = n - 1; i >= 0; i--) { 
  if(a[i] == 1) { 
    one_pos[i] = max(one_pos[i + 1], i); 
  }
 }
 int64_t ret = 0; 
 for(int i = 0; i < n; i++) { 
  int64_t sum = a[i], prod = a[i]; 
  for(int j = i + 1; j < n; j++) { 
    if(a[j] == 1) { 
     int cnt1 = one_pos[j] - j + 1;
     j = one_pos[j]; 
     if(sum < prod && sum + cnt1 >= prod) { 
      ret++;   
     }
     sum += cnt1;
     continue;     
    }
    sum += a[j]; 
    prod *= a[j]; 
    ret += (sum == prod); 
    if(sum + suffix[j + 1] < prod) { 
      break;   
    }
  }
 }
 cout << ret << '\n'; 
 return 0; 
}