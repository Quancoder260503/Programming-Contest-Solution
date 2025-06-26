#include "bits/stdc++.h"
 
using namespace std; 
 
const int MOD = 998244353; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
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

int64_t dp[3005][3005][2];
int N, M, sumA, sumB; 

int64_t F(int pos, int add, int type) { 
  if(pos == 0) return 1; 
  int64_t &ret = dp[pos][add][type];
  if(ret != -1) return ret; 
  int sub = M - pos - add; 
  if(sub < 0) return ret = 0; 
  int64_t den = mod_inv(sumA + sumB + add - sub, MOD); 
  if(type) { 
   ret = (sumA + add + 1  ) % MOD * den % MOD * F(pos - 1, add + 1, type) % MOD + 
         max(0, sumB - sub) % MOD * den % MOD * F(pos - 1, add, type) % MOD; 
   ret %= MOD; 
  } else { 
   ret = max(0, sumB - sub - 1) % MOD * den % MOD * F(pos - 1, add, type) % MOD + 
            (sumA + add       ) % MOD * den % MOD * F(pos - 1, add + 1, type) % MOD; 
   ret %= MOD; 
  }
  return ret; 
 } 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> N >> M; 
 vector<int64_t>a(N), b(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }  
 for(int i = 0; i < N; i++) { 
  cin >> b[i]; 
 }
 sumA = sumB = 0; 
 for(int i = 0; i < N; i++) { 
  (a[i] ? sumA : sumB) += b[i]; 
 }
 memset(dp, -1, sizeof(dp)); 
 F(M, 0, 0); 
 F(M, 0, 1); 
 for(int i = 0; i < N; i++) { 
  cout << b[i] % MOD * F(M, 0, a[i]) % MOD << '\n'; 
 }
 return 0; 
}



/*

Easy version 

int64_t dp[102][52][52][52][2]; 

int main(void) {  
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N, M;
 cin >> N >> M; 
 vector<int>a(N), b(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }  
 for(int i = 0; i < N; i++) { 
  cin >> b[i]; 
 }
 int sumA = 0, sumB = 0; 
 for(int i = 0; i < N; i++) { 
  (a[i] ? sumA : sumB) += b[i]; 
 }
 memset(dp, -1, sizeof(dp)); 
 function<int64_t(int, int, int, int, int)> F = [&](int w, int pos, int j, int k, int type) -> int64_t { 
  if(pos == 0) return w; 
  int64_t &ret = dp[w][pos][j][k][type]; 
  if(ret != -1) return ret;
  int64_t den = mod_inv(sumA + sumB + j - k, MOD); 
  if(type) { 
    int64_t expectedA = (sumA + j - w) % MOD * den % MOD * F(w, pos - 1, j + 1, k, type) % MOD;
    int64_t expectedB = w % MOD * den % MOD * F(w + 1, pos - 1, j + 1, k, type) % MOD; 
    int64_t expectedC = (sumB - k) % MOD * den % MOD * F(w, pos - 1, j, k + 1, type) % MOD;  
    ret = expectedA + expectedB + expectedC; 
  } else { 
    int64_t expectedA = (sumA + j) % MOD * den % MOD * F(w, pos - 1, j + 1, k, type) % MOD;
    int64_t expectedB = (w ? w % MOD * den % MOD * F(w - 1, pos - 1, j, k + 1, type) % MOD : 0); 
    int64_t expectedC = max(0, sumB - k - w) % MOD * den % MOD * F(w, pos - 1, j, k + 1, type) % MOD;  
    ret = expectedA + expectedB + expectedC; 
  }
  ret %= MOD; 
  return ret; 
 }; 
 for(int i = 0; i < N; i++) { 
  cout << F(b[i], M, 0, 0, a[i]) << '\n'; 
 }
 return 0;
}
*/ 