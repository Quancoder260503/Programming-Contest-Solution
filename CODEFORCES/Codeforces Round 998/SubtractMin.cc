#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int MOD = 998244353; 

class SubtractMin { 
  public:   
   void solve() { 
    int N; 
    cin >> N;
    vector<int>a(N); 
    for(int i = 0; i < N; i++) { 
     cin >> a[i]; 
    } 
    for(int i = 1; i < N; i++) { 
     if(a[i] < a[i - 1]) { 
      cout << "NO\n"; 
      return; 
     }
     int m = min(a[i], a[i - 1]); 
     a[i] -= m; 
     a[i - 1] -= m; 
    }
    cout << "YES\n"; 
    return; 
   }
  private: 
   int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
    int64_t res = 1;
    while (b > 0) {
     if (b & 1) res = (res * a) % p;
     a = (a * a) % p;
     b >>= 1;
    }
    return res;
   }

   int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

   int64_t Comb(int64_t a, int64_t b) { 
    int64_t ans = 1; 
    for(int x = a - b + 1; x <= a; x++) { 
     ans = ans % MOD * x % MOD; 
    }
    for(int x = 2; x <= b; x++) { 
     ans = ans % MOD * mod_inv(x, MOD) % MOD;    
    }
    return ans; 
   }
};


int main(void) {  
 int T; 
 SubtractMin problem; 
 for(cin >> T; T--; ) { problem.solve(); }
 return 0; 
}