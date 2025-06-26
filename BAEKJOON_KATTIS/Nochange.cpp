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
long long check(int pos, int c){
       int low = pos;
       int high = n;
       long long val = PF[pos] + c;
       while(low < high){
           int mid = (low + high + 1) >> 1; 
           if(PF[mid] <= val) low = mid; 
           else high = mid - 1; 
       }
       return low; 
}
signed main(void){
     scanf("%d%d",&k,&n);
     for(int i = 0; i < k; i++){
          scanf("%lld",&Cost[i]); 
     }
     for(int i = 1; i <= n; i++){
          scanf("%lld",&A[i]); 
          PF[i] = PF[i - 1] + A[i]; 
     }
     long long ans = -1; 
     for(int mask = 0; mask < (1 << k); mask++){
            for(int i = 0; i < k; i++){
                if(mask & (1 << i)){
                    DP[mask] = max(DP[mask], check(DP[mask xor (1 << i)],Cost[i])); 
                }
            }
            if(DP[mask] == n){
                long long sum = 0;
                for(int i = 0; i < k; i++){
                    if(mask & (1 << i)) continue;
                    sum = sum + Cost[i];
                }
                ans = max(sum,ans); 
            }
     }
     printf("%lld\n",ans); 
     return 0; 
}












