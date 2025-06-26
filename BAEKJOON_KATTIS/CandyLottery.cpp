#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define MAX 102
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k,a,b;  
long double DP[MAX][MAX * 6]; 
signed main(void){
     scanf("%d%d",&n,&k);
      long double div = (long double) k;    
      long double ans = 0; 
      for(int i = 1; i <= k; i++){
           long double a,b;
           a = b = 1.0; 
           for(int j = 0; j < n; j++){
                a = a * i / div;
                b = b * (i - 1) / div; 
           }
           ans += (long double) (a - b) * i;
      }
     printf("%0.6llf\n",ans); 
     return 0; 
}

















