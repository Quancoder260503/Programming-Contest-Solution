#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define inf 100000000000
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k,a,b;  
long long DP[N]; 
long long A[N];
long long Cost[N];
long long PF[N];   
long long Eulerphi(long long x){
      long long ans = x;
      vector<int>primes;
      for(int i = 2; i * i <= x; i++){
            if(x % i == 0){
                ans = ans / i; 
                primes.push_back(i); 
            }
            while(x % i == 0) x = x / i; 
      }
      if(x > 1){
         ans = ans / x; 
         primes.push_back(x); 
      }
      for(int i = 0; i < (int) primes.size(); i++){
           ans = ans % mod * (primes[i] - 1) % mod;  
      }
      return ans;
}
void solve(){
     scanf("%d",&n);
     for(int i = 0; i < n; i++){
             scanf("%lld",&A[i]); 
     }
     long long ans = 1;
     for(int i = 0; i < n; i++){
         ans = ans % mod * Eulerphi(A[i]) % mod; 
     }
     printf("%lld\n",ans); 
}
signed main(void){
     int t;
     scanf("%d",&t);
     while(t--){
         solve(); 
     }
     return 0; 
}












