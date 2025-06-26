#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N];
long long A[N];  
long long DP[N]; 
int n,k;  
signed main(void){
     scanf("%d",&n); 
     if(n <= 1){
        printf("1\n");
        return 0;
     }
     DP[0] = 1;
     DP[1] = 1; 
     DP[2] = 2; 
     for(int i = 3; i <= n; i++){
        DP[i] = (DP[i - 1] + DP[i - 2]) % mod; 
     }
     long long ans = 0;
     // gcd(F[i],F[j]) = F[gcd(i,j)] for Fibonacci numbers :))) 
     for(int i = 1; i <= n; i++){
        ans += DP[gcd(i + 1, n + 1) - 1]; 
        ans = ans % mod; 
     }
     printf("%lld\n",ans); 
     return 0; 
}