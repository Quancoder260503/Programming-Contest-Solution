#include "bits/stdc++.h"
using namespace std; 
#define MAX 5000
int g[MAX][MAX];
bool vis[MAX][MAX];  
int n,m; 
int dx[9] = {1,-1,0,0,0,1,-1,-1,1};
int dy[9] = {0,0,-1,1,0,-1,1,-1,1}; 
signed main(void)
{
     scanf("%d%d",&n,&m);
     for(int i = 1; i <= n + 2; i++)
     {
         for(int j = 1; j <= m + 2; j++)
         {
             scanf("%d",&g[i][j]); 
         }
     }
     for(int i = 1; i <= n + 2; i++)
     {
         for(int j = 1; j <= m + 2; j++)
         {
              if(g[i - 1][j - 1])
              {
                   vis[i][j] = 1; 
                   for(int k = 0; k < 9; k++)
                   {
                       int tx = i + dx[k];
                       int ty = j + dy[k]; 
                       g[tx][ty]--;  
                   }
              }
         }
     }
     for(int i = 1; i <= n + 2; i++)
     {
         for(int j = 1; j <= m + 2; j++)
         {
             if(g[i][j] != 0)
             { 
                 puts("impossible");
                 return 0; 
             }
         }
     }
     for(int i = 2; i < n + 2; i++)
     {
         for(int j = 2; j < m + 2; j++)
         {
              if(vis[i][j]) printf("X");
              else printf("."); 
         }
         printf("\n"); 
     }
     return 0; 
}