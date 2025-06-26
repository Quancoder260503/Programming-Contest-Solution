#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;

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

vector<int64_t>multiply(const vector<int64_t>&a, const vector<int64_t>&b) { 
  vector<int64_t>ret(sz(a) + sz(b) - 1); 
  for(int i = 0; i < sz(a); i++) { 
    for(int j = 0; j < sz(b); j++) { 
      (ret[i + j] += a[i] % MOD * b[j] % MOD) %= MOD; 
    }
  }
  return ret; 
}

vector<int64_t> polyIntegrate(vector<int64_t>g) { 
  for(int i = 0; i < sz(g); i++) { 
    g[i] = g[i] % MOD * mod_inv(i + 1, MOD) % MOD; 
  }
  g.insert(g.begin(), 0); 
  return g; 
}

vector<int64_t> polyDerivative(vector<int64_t>g) { 
  for(int i = 0; i < sz(g); i++) { 
    g[i] = g[i] % MOD * i % MOD;  
  }
  g.erase(g.begin()); 
  return g; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N; 
  cin >> N; 
  vector<int64_t>L(N), R(N), inv(N); 
  vector<int>range; 
  for(int i = 0; i < N; i++) { 
    cin >> L[i] >> R[i];
    range.push_back(L[i]);  
    range.push_back(R[i]); 
    inv[i] = mod_inv(R[i] - L[i], MOD); 
  }
  sort(range.begin(), range.end()); 
  range.erase(unique(range.begin(), range.end()), range.end()); 
  int64_t ans = 0;
  for(int ind = 0; ind + 1 < sz(range); ind++) {
    vector<int64_t>ret {1}; 
    int flag = true; 
    for(int i = 0; i < N; i++) { 
      if(L[i] >= range[ind + 1]) { 
        flag = false; 
        break; 
      }
      if(R[i] > range[ind]) {
        vector<int64_t>newR = {MOD - L[i] % MOD * inv[i] % MOD, inv[i]}; 
        ret = multiply(ret, newR); 
      }
    }
    if(!flag) continue; 
    ret = polyDerivative(ret);
    ret = multiply(ret, {0, 1});
    ret = polyIntegrate(ret);   
    for(int i = 0; i < sz(ret); i++) { 
      (ans += ret[i] % MOD * (mod_pow(range[ind + 1], i, MOD) + MOD - mod_pow(range[ind], i, MOD)) % MOD) %= MOD; 
    }
    //cout << ans << '\n'; 
  }
  for(int i = 0; i < N; i++) { 
    ans = ans % MOD * (R[i] - L[i]) % MOD * (i + 1) % MOD; 
  }
  ans = ans % MOD * (N + 1) % MOD; 
  cout << ans << '\n'; 
  return 0; 
}
