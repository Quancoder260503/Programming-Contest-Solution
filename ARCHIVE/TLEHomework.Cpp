#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 6e5 + 100;
const int INF = 1e7 + 10; 
const int mod = 1e9 + 13;
long long n,m,q,dsz,M;
int timer = 1;
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
    scanf("%lld", &n); 
    long long p = n % 180 * 45 % 180;
    if(n % 4 == 0){
         long long ansp = (binpow(2,n - 2) % mod + binpow(2,(n - 2) / 2) % mod + mod) % mod;  
         long long ansn = (binpow(2,n - 2) % mod - binpow(2,(n - 2) / 2) % mod + mod) % mod; 
         if(n % 8 == 0) printf("%lld \n",ansp);
         else printf("%lld \n",ansn); 
         return 0; 
    }
    if(n % 2 == 0){
         printf("%lld",binpow(2, n - 2));
         return 0; 
    }
    if(n == 1){
         printf("%d \n",1);
         return 0; 
    }
    long long ansp = (binpow(2,(n - 3) / 2) % mod + binpow(2,n - 2) % mod + mod) % mod; 
    long long ansn = (-binpow(2,(n - 3) / 2) % mod + binpow(2,n - 2) % mod + mod) % mod; 
    if(n % 8 == 5 or n % 8 == 3) printf("%lld \n",ansn);
    else printf("%lld \n",ansp); 
    return 0; 
}