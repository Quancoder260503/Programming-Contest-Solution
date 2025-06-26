#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 2e8 + 10
#define MAX (int) 5e4 + 10
#define lint long long
lint arr[MAX];
int n, m; 
bool vis[MAXN];
signed main(void)
{
    int cnt = 0; 
    scanf("%d %d", &arr[1], &m);
    set<int>sval;
    int start = 1; 
    for(int i = 1; i < MAX; i++)
    {
         if(arr[1] < MAXN)
         {
             vis[arr[1]] = 1;
         }
         for(auto it = sval.begin(); it != sval.end(); it++)
         {
             if(arr[1] - *it < MAXN)
             {
                 vis[arr[1] - *it] = 1; 
             }
         } 
         while(vis[start])
         {
             start += 1; 
         }
         sval.insert(arr[1]);
         arr[1] += start;
         if(vis[m])
         {
             printf("%d\n", i);
             return 0;
         }
    }
    return 0; 
}