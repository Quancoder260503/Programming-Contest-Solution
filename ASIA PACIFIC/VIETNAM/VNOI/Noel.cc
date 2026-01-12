#include "bits/stdc++.h"

#define sz(x) int(x.size())

using namespace std;


template<class T> 
struct fenwick { 
  vector<T>bit; 
  int n; 
  fenwick(int _n) : n(_n) { 
   bit.assign(n, 0); 
   return; 
  }
  void update(int i, T x) { 
   for(i++; i < n; i += i & (-i)) { 
    bit[i] = max(bit[i], x); 
   }
  }
  T query(int i) { 
   T ret = 0; 
   for(i++; i > 0; i -= i & (-i)) { 
    ret = max(ret, bit[i]); 
   }
   return ret;
  }
}; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n, d;  
  cin >> n >> d;
  n = 2 * n;  
  vector<int>a(n); 
  for(auto &x : a) { 
   cin >> x; 
  }
  int ans = 0; 
  for(int z = 1; z <= n; z++) { 
   vector<int>array_a, array_b; 
   unordered_map<int, int>mp; 
   for(int j = 0; j < z; j++) { 
    array_a.push_back(a[j]); 
   }
   for(int j = z; j < n; j++) { 
    array_b.push_back(a[j]); 
   }
   for(int j = 0; j < array_b.size(); j++) { 
    mp[array_b[j]] = j; 
   }
   fenwick<int> fenw(sz(array_b) + 7); 
   int ret = 0; 
   for(int j = 0; j < array_a.size(); j++) { 
    vector<int>ind; 
    for(int x = -d; x <= d; x++) { 
      if(mp.count(array_a[j] + x)) { 
       ind.push_back(mp[array_a[j] + x]); 
      }
    }
    sort(ind.rbegin(), ind.rend()); 
    for(auto &x : ind) { 
     int opt = 1 + fenw.query(x - 1);
     ret = max(ret, opt); 
     fenw.update(x, opt);  
    }
   }
   /*
   vector<vector<int>>dp(z, vector<int>(n - z, -1)); 
   function<int(int, int)> memo = [&](int x, int y) { 
    if(x == z || y == n - z) return 0; 
    int &ret = dp[x][y]; 
    if(ret != -1) return ret; 
    ret = max(memo(x + 1, y), memo(x, y + 1)); 
    if(abs(array_a[x] - array_b[y]) <= d) { 
      ret = max(ret, 1 + memo(x + 1, y + 1)); 
    } 
    return ret;
   }; 
   */ 
   ans = max(ans, ret); 
  }
  cout << ans << '\n'; 
  return 0; 
}

