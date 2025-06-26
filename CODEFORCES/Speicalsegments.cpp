#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
int arr[MAXN];
int n;  
int L[MAXN], R[MAXN]; 
int cnt[MAXN]; 
signed main(void)
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]); 
    }
    reverse(arr + 1, arr + n + 1); 
    if(is_sorted(arr + 1, arr + n + 1))
    {
         puts("0");
         return 0;
    }
    reverse(arr + 1, arr + n + 1);
    if (is_sorted(arr + 1, arr + n + 1))
    {
         puts("0");
         return 0;
    }
    stack<int>stk; 
    for(int i = 1; i <= n; i++)
    {
         while(stk.size() && arr[stk.top()] <= arr[i])
         {
             stk.pop(); 
         }
         L[i] = stk.size() ? stk.top() : 0; 
         stk.push(i); 
    }
    while(stk.size()) stk.pop();
    for (int i = n; i > 0; i--)
    {
         while (stk.size() && arr[stk.top()] <= arr[i])
         {
             stk.pop();
         }
         R[i] = stk.size() ? stk.top() : n + 1;
         stk.push(i); 
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++)
    {
         int lef = L[i] + 1;
         int rig = R[i] - 1;
         for(int j = lef; j < i; j++)
         {
             cnt[arr[j]] += 1; 
         }
         for(int j = i + 1; j <= rig; j++)
         {
             ans += cnt[arr[i] - arr[j]]; 
         }
         for(int j = lef; j < i; j++)
         {
             cnt[arr[j]] = 0; 
         }
    }
    printf("%lld\n", ans); 
    return 0; 
}