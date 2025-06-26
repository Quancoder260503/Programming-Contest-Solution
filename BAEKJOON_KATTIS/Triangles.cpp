#include "bits/stdc++.h"
#pragma GCC target("popcnt")
#include <stdio.h>
#include <algorithm>
#include <array>
using namespace std;
#define N 1500000
#define M 600
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
int n,k;  
bitset<M>dp[M][M];
Vec operator - (Vec AB, Vec AC){
    return Vec(AB.x - AC.x, AB.y - AC.y); 
}
long long cross(Vec AB, Vec AC) {
    return (1ll) * AB.x * AC.y - (1ll) * AB.y * AC.x; 
}
long long cross3(Vec AB, Vec AC, Vec BC) {
    Vec X = AC - AB; 
    Vec Y = BC - AB; 
    return  cross(X,Y);
}
using Point = Vec;
Point P[N];
signed main(void){
     scanf("%d",&n);
     for(int i = 1; i <= n; i++)
     {
        scanf("%lld%lld",&P[i].x, &P[i].y); 
     } 
     for(int i = 1; i <= n; i++)
     {
        for(int j = 1; j <= n; j++)
        {
            if(i == j) continue; 
            for(int k = 1; k <= n; k++)
            { 
                if(cross3(P[i],P[j],P[k]) > 0){
                    dp[i][j][k] = 1; 
                }
            }
        }
     }
     long long ans = 0;
     for(int i = 1; i <= n; i++)
     {
         for(int j = i + 1; j <= n; j++)
         {
            for(int k = j + 1 ; k <= n; k++)
            {
                array<int,3> curr; 
                curr[0] = i; curr[1] = j; curr[2] = k; 
                if(cross3(P[i],P[j],P[k]) < 0) swap(curr[1],curr[2]); 
                bitset<M>temp = dp[curr[0]][curr[1]] & dp[curr[1]][curr[2]] & dp[curr[2]][curr[0]]; 
                if(temp.count() > 0) ans += 1; 
            }
         }
     }
     printf("%lld\n",ans); 
     return 0; 
}