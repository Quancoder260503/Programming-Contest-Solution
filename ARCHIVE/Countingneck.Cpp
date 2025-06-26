#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e7 + 1;
const int inf = 1e7+5;
const int mod = 1e9 + 7; 
long long n,m,k,q;
long long fac[N];
long long inv[N];
long long finv[N]; 
long long binpow(long long a,long long b){
     if(b == 0) return 1; 
     long long ans = 1; 
     while(b > 0){
           if(b & 1) ans = ans % mod * a % mod;
           a = a % mod * a % mod;
           b >>= 1;
     }
     return ans; 
}
void binom_init() {
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    for(int i = 2; i < N; i++){
        fac[i] = fac[i - 1] % mod * i % mod;
        inv[i] = mod - mod / i  % mod * inv[mod % i] % mod;
        finv[i] = ((finv[i - 1] % mod) % mod) % mod * ((inv[i] % mod) % mod)% mod;
    }
}
long long binom(long long r, long long n){
    if( n < r || n < 0 || r < 0) return 0;
    return (fac[n] * finv[r] % mod * finv[n - r] % mod) % mod;
}
int main(){
     scanf("%d%d",&n,&m);
     binom_init();
     long long ans = 0; 
     for(long long i = 0; i < n; i++){ 
          ans = (ans + mod + binpow(m,__gcd(n,i)) % mod) % mod;
     }
     ans = ans % mod * binpow(n,mod - 2) % mod;
     cout<<ans<<endl;
}