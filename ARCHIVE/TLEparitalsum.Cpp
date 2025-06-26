#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 6e5 + 100;
const int INF = 1e7 + 10; 
const int mod = 1e9 + 7;
long long n,m,q,dsz,M,k;
int timer = 1;
long long dp[N + 1]; 
long long a[N + 1]; 
long long d[N + 1];
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
int main(){
    scanf("%d", &n); 
    for(int i = 1; i <= n; i++) scanf("%lld",&a[i]); 
    scanf("%lld",&k); 
    d[1] = 1;
    for(int i = 2; i <= n; i++){
         d[i] = d[i - 1] % mod * (k + i - 2) % mod * binpow(i - 1, mod - 2) % mod; 
    }
    for(int i = 1; i <= n; i++){
         for(int j = i; j > 0; j--){
             dp[i] = (dp[i] + d[i - j + 1] % mod * a[j] % mod) % mod; 
         }
    }
    for(int i = 1; i <= n; i++) printf("%lld ",dp[i]);
}