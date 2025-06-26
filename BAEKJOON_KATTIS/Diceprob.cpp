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
     scanf("%d%d%d",&n,&a,&b);
     DP[0][0] = 1.0;
     for(int i = 1; i <= n; i++){
          for(int j = 0; j <  MAX * 6; j++){
              for(int k = 1; k <= 6; k++){
                    if(j >= k){
                        DP[i][j] = (DP[i][j] + DP[i - 1][j - k]);
                    }
              }
              DP[i][j] = DP[i][j] / 6.0;
          }
     }
     long double ans = 0;
     for(int i = a; i <= b; i++){
          ans +=  DP[n][i]; 
     }
     printf("%0.6llf",ans); 
     return 0; 
}






















