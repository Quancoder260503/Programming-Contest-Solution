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
int w;
signed main(void){
     scanf("%d%d",&w,&n);
     long long ans = 0; 
     for(int i = 0; i < n; i++){
           int l,r; scanf("%d%d",&l,&r); 
           ans += 1ll * l * r; 
     } 
     ans = ans / w;
     printf("%lld\n",ans);
     return 0; 
}