#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 2e5 + 10
vector<int> arr;
int n, k; 
void dfs(int depth, vector<int>&curr)
{
     if(!curr.size() || depth <= 0) return;
     if(depth >= (int) curr.size() / 2 + 1)
     {
         int pos = min(depth, (int) curr.size()) - 1;
         printf("%d ", curr[pos]);
         for (int i = 0; i < pos; i++)
         {
             printf("%d ", curr[i]); 
          }
          for(int i = pos + 1; i < curr.size(); i++)
          {
             printf("%d ", curr[i]); 
          }
          return;
     }
     int mask; 
     for(mask = depth - 1; mask >= 0; mask--)
     {
         if((1 << mask) <= curr.size())
         {
             break; 
         }
     }
     int pos = (1 << mask) - 1; 
     printf("%d ", curr[pos]); 
     vector<int> lef(curr.begin(), curr.begin() + pos);
     dfs(depth - 1, lef);
     vector<int> rig(curr.begin() + pos + 1, curr.end());
     dfs(depth - 1, rig);
     return; 
}
signed main(void)
{
    scanf("%d %d", &n, &k); 
    int curr = 1; 
    for(int i = 0; i < k; i++)
    {
         curr = curr * 2; 
         if(curr > n) break; 
    }  
    if(n >= curr || k > n) 
    {
         puts("impossible");
         return 0; 
    }
    for(int i = 1; i <= n; i++)
    {
         arr.push_back(i); 
    }
    dfs(k, arr); 
    return 0;
}