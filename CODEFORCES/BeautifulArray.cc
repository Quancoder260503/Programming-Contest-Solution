#include "bits/stdc++.h"

using namespace std;  

#define sz(x) int(x.size())

const int64_t oo = 1e17; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int n, x; 
  cin >> n >> x; 
  vector<int>a(n + 1); 
  for(int i = 1; i <= n; i++) { 
   cin >> a[i]; 
  }
  vector<int64_t>prefix(n + 2), suffix(n + 2), opt_prefix(n + 2), opt_suffix(n + 2);
  for(int i = 1; i <= n; i++) { 
   prefix[i] = a[i] + prefix[i - 1]; 
  }
  for(int i = n; i >= 0; i--) { 
   suffix[i] = a[i] + suffix[i + 1]; 
  }
  set<int64_t>ms;
  ms.insert(0); 
  for(int i = 1; i <= n; i++) { 
   opt_prefix[i] = max(opt_prefix[i], prefix[i] - *ms.begin()); 
   ms.insert(prefix[i]);
  }
  ms.clear(); 
  ms.insert(0); 
  for(int i = n; i > 0; i--) { 
   opt_suffix[i] = max(opt_suffix[i], suffix[i] - *ms.begin()); 
   ms.insert(suffix[i]); 
  }
  int64_t ret = 0;; 
  int64_t opt_so_far = -oo; 
  for(int i = n; i >= 0; i--) { 
   ret = max(ret, opt_prefix[i] + max(0LL, - prefix[i] * x + opt_so_far)); 
   opt_so_far = max(opt_so_far, opt_suffix[i + 1] + prefix[i] * x); 
  } 
  cout << ret << '\n'; 
  return 0; 
}
