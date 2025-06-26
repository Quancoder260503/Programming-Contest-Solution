#include "bits/stdc++.h"
using namespace std;
#define N 1000005 
#define mp make_pair
priority_queue<pair<int,int> >pq; 
int W[N]; 
int cnt[N];
int day[N];
int m,n,d,h;  
vector<int>C[N];   
vector<int>ans[N]; 
signed main(void){
    scanf("%d%d%d%d",&m,&n,&d,&h); 
    for(int i = 1; i <= m; i++)
    {
        scanf("%d",&W[i]);
        pq.push(mp(W[i],i));  
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d",&day[i]); 
    }
    for(int i = 1; i <= n; i++)
    {  
         if(cnt[i] > day[i])
         {
             printf("-1");
             return 0; 
         }
         else{
             while(cnt[i] < day[i])
             {
                if(pq.empty()){
                  printf("-1");
                  return 0; 
                }
                pair<int,int> curr = pq.top();
                pq.pop();
                if(W[curr.second] < d){
                      printf("-1");
                      return 0; 
                }
                W[curr.second] = W[curr.second] - d; 
                for(int j = i; j < i + d; j++) 
                {
                    cnt[j] += 1; 
                }
                if(W[curr.second] >= d && i + d + h - 1 <= n){
                     C[i + d + h - 1].push_back(curr.second);
                }
                ans[curr.second].push_back(i); 
             }
         }
         for(int j = 0; j < C[i].size(); j++)
         {
              int curr = C[i][j]; 
              pq.push(mp(W[curr],curr)); 
         }
    }
    printf("1\n");
    for(int i = 1; i <= m; i++)
    {
         for(int j = 0; j < ans[i].size(); j++)
         {
            printf("%d ",ans[i][j]); 
         }
         printf("\n"); 
    }
    return 0; 
}