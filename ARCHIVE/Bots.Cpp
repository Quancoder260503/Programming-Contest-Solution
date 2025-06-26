#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
const int M = 4e5+1;
const int N = 2e6 + 1000;
const int inf = 1e7+5;
const int mod = 1e9 + 7;
long long n,m,k,t;
vector<long long>finv;
vector<long long>fac;
vector<long long>inv;
void binom_init() {
    fac.resize(N + 1);
    finv.resize(N + 1);
    inv.resize(N + 1);
    fac[0] = fac[1] = 1;
    inv[1] = 1;
    finv[0] = finv[1] = 1;
    for(int i = 2 ; i < N + 1; i++){
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod-mod/i*inv[mod % i]%mod;
        finv[i] = finv[i-1]*inv[i]%mod;
    }
}
long long binom(long long n, long long r){
    if(n<r || n<0 || r<0) return 0;
    return (fac[n]*finv[r]%mod*finv[n-r]%mod)%mod;
}
int main(){
      scanf("%d",&n); 
      binom_init();
      long long ans = (binom(2 * (n + 1),n + 1) - 1 + mod) % mod;
      printf("%lld\n",ans); 
}