#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e3 + 10;
const long long INF = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p;
vector<int>adj[N + 1];
long long row[N + 1];
long long col[N + 1];
long long g[N + 1][N + 1];
int main(){
      scanf("%d%d",&n,&m);
      long long xrow = 0; 
      long long xcol = 0; 
      for(int i = 1; i <= n; i++){
          scanf("%lld", row + i);
          xrow = xrow xor row[i]; 
      }
      for(int i = 1; i <= m; i++){
           scanf("%lld", col + i);
           xcol = xcol xor col[i]; 
      }
      if(xrow != xcol){
            printf("NO\n");
            return 0; 
      }
      printf("YES\n"); 
      for(int i = 1; i <= n; i++) g[i][m] = row[i];
      for(int i = 1; i <= m; i++) g[n][i] = col[i];
      g[n][m] = col[m] xor row[n] xor xrow;
      for(int i = 1; i <= n; i++){
             for(int j = 1; j <= m; j++){
                   printf("%lld ",g[i][j]); 
             }
             printf("\n"); 
      }
      return 0;
}