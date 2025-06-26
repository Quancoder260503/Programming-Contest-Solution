#include "bits/stdc++.h"
#pragma GCC target("popcnt")
#include <array> 
using namespace std; 
#define N 1000005
#define x first
#define y second
typedef pair<long long,long long> Vec; 
const int mod = 1e9 + 7; 
int n,k;  
long long res[N]; 
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
long long dist(Vec AB, Vec AC){
    return 1ll * (AC.x - AB.x) *(AC.x - AB.x) + 1ll * (AC.y - AB.y) * (AC.y - AB.y);
}
Vec P[N]; 
#define MAX 305
bitset<MAX>DP[MAX][MAX]; 
signed main(void){
     scanf("%d",&n);
     for(int i = 0; i < n; i++){
          scanf("%d%d",&P[i].x,&P[i].y); 
     }
     for(int i = 0; i < n; i++)
     {
           for(int j = 0; j < n; j++)
           {
                 if(i == j) continue; 
                 for(int k = 0; k < n; k++)
                 {
                     if(cross3(P[i],P[j],P[k]) > 0)
                     {
                         DP[i][j][k] = 1; 
                     }
                 }
           }
     }
     for(int i = 0; i < n; i++)
     {
          for(int j = i + 1; j < n; j++)
           {
               for(int k = j + 1; k < n; k++)
               {  
                    array<int,3>curr = {i,j,k};
                    if(cross3(P[i],P[j],P[k]) < 0) swap(curr[1],curr[2]); 
                    bitset<MAX>state = DP[curr[0]][curr[1]] & DP[curr[1]][curr[2]] & DP[curr[2]][curr[0]]; 
                    res[state.count()] += 1; 
                }
           }
     }
     for(int i = 0; i < n - 2; i++)
     { 
          printf("%lld\n",res[i]); 
     }
     return 0;
}