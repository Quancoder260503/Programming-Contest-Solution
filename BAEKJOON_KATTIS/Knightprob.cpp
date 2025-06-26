#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 51
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
int n,k,x,y;
long double DP[N][N][2];
int dx[8] = {-2,-1,1,2,2,1,-1,-2};
int dy[8] = {1,2,2,1,-1,-2,-2,-1};    
signed main(void){
     scanf("%d%d%d%d",&n,&x,&y,&k);
     DP[--x][--y][0] = 1.0;
     for(int t = 0; t < k; t++){
          for(int i = 0; i < n; i++){
               for(int j = 0; j < n; j++){
                    DP[i][j][1] = 0.0;
               }
          }
          for(int i = 0; i < n; i++){
               for(int j = 0; j < n; j++){
                    for(int dir = 0; dir < 8; dir++){
                         int tx = dx[dir] + i;
                         int ty = dy[dir] + j;
                         if(tx < 0 || tx > n - 1) continue;
                         if(ty < 0 || ty > n - 1) continue; 
                         DP[tx][ty][1] += (DP[i][j][0] / 8.0);  
                    }
               }
          }
          for(int i = 0; i < n; i++){
               for(int j = 0; j < n; j++){
                      DP[i][j][0] = DP[i][j][1];
               }
               printf("\n"); 
          }
     }
     long double ans = 0; 
     for(int i = 0; i < n; i++){
          for(int j = 0; j < n; j++){
                ans += DP[i][j][0]; 
          }
     } 
     printf("%0.10llf\n",ans); 
     return 0; 
}