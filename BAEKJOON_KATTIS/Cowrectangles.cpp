#include "bits/stdc++.h"
#pragma GCC target("popcnt")
#include <stdio.h>
#include <algorithm>
#include <array>
using namespace std;
#define N 1500000
#define MAX 1002
#define M 600
#define mp make_pair
#define x first 
#define y second
typedef pair<long long,long long> Vec; 
typedef long double ldb;
const int mod = 1e9 + 7; 
int n,k;  
char type[N]; 
using Point = Vec;
pair<int,int> mat[MAX][MAX]; 
Point P[N]; 
vector<int>lst;
signed main(void){
     scanf("%d",&n);
     for(int i = 1; i <= n; i++)
     {
        scanf("%lld%lld",&P[i].x,&P[i].y);
        cin >> type[i];
        if(type[i] == 'H') mat[P[i].x][P[i].y].first += 1; 
        else mat[P[i].x][P[i].y].second += 1; 
        lst.push_back(P[i].x); 
     }
     for(int i = 1; i < MAX; i++)
     {
          for(int j = 1; j < MAX; j++)
          {
               mat[i][j].first += mat[i - 1][j].first;
               mat[i][j].second += mat[i - 1][j].second; 
          }
     }
     pair<int,int>ans = mp(0,INT_MIN); 
     for(int i = 0; i < lst.size(); i++)
     {
        for(int j = 0; j < lst.size(); j++)
        {
             if(lst[i] <= lst[j]){
                  int count = 0;
                  int cy = 1;
                  for(int k = 1; k < MAX; k++)
                  {
                     int h = mat[lst[j]][k].first;
                     int g = mat[lst[j]][k].second; 
                     if(lst[i] > 0){
                         h = h - mat[lst[i] - 1][k].first;
                         g = g - mat[lst[i] - 1][k].second; 
                     } 
                     if(g){
                          count = 0; 
                          cy = k + 1; 
                          continue;
                     }
                     count += h;
                     ans = max(ans, mp(count, -(lst[j] - lst[i]) * (k - cy))); 
                     if(!count) cy = k + 1;   
                  }
             }
        }
     }
     printf("%d\n%d",ans.first,-ans.second); 
     return 0; 
}