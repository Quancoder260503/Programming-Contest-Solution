#include "bits/stdc++.h"
using namespace std;
int n; 
#define N 300005
bitset<N>dp; 
long long A[N]; 
signed main(void){
     // determine if after removing the ith element, is it able to divide remainders into two equals set
     scanf("%d",&n); 
     for(int i = 1; i <= n; i++)
     {
          scanf("%d",&A[i]); 
     }
     vector<int>ans;
     for(int i = 1; i <= n; i++)
     {   
        vector<int>tmp; 
        long long sum = 0;
        for(int j = 1; j <= n; j++)
        { 
             if(i == j) continue; 
             tmp.push_back(A[j]); 
             sum += A[j];    
        }      
        if(sum & 1) continue; 
        dp.reset();
        dp[0] = 1; 
        for(int j = 0; j < tmp.size(); j++)
        {
             dp |= (dp << tmp[j]);
        }
        if(dp[sum / 2]) ans.push_back(i); 
     }
     printf("%d\n",(int) ans.size());
     for(int i = 0; i < ans.size(); i++)
     {
           printf("%d ",ans[i]); 
     }
     return 0; 
}