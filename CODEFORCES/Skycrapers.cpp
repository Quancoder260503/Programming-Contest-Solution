#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10
#define lint long long
#define pii pair<lint, lint> 
#define mp make_pair
int arr[MAXN]; 
int n; 
lint dp[MAXN][2]; 
signed main(void)
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]); 
    }
    stack<int>stk; 
    for(int i = 1; i <= n; i++)
    {
         while(stk.size() && arr[i] < arr[stk.top()])
         {
             stk.pop(); 
         }
         int last = stk.size() ? stk.top() : 0; 
         dp[i][0] = 1LL * arr[i] * (i - last) + dp[last][0]; 
         stk.push(i); 
    }
    while(stk.size()) stk.pop();
    for (int i = n; i > 0; i--)
    {
         while (stk.size() && arr[i] < arr[stk.top()])
         {
             stk.pop();
         }
         int last = stk.size() ? stk.top() : n + 1;
         dp[i][1] += 1LL * arr[i] * (last - i) + dp[last][1];
         dp[i][0] += dp[i][1] - arr[i]; 
         stk.push(i); 
    }
    pii ans = mp(0, 0); 
    for(int i = 1; i <= n; i++)
    {
         ans = max(ans, mp(dp[i][0], 1LL * i)); 
    }
    int curr = arr[ans.second]; 
    vector<int>lef, rig; 
    for(int i = ans.second; i <= n; i++)
    {
         if(curr > arr[i])
         {
             curr = arr[i]; 
         }
         rig.push_back(curr); 
    }
    curr = arr[ans.second];
    for (int i = ans.second - 1; i > 0; i--)
    {
         if (curr > arr[i])
         {
             curr = arr[i];
         }
         lef.push_back(curr);
    }
    reverse(lef.begin(), lef.end());
    for(int i = 0; i < lef.size(); i++)
    {
        printf("%d ", lef[i]); 
    }
    for (int i = 0; i < rig.size(); i++)
    {
        printf("%d ", rig[i]);
    }
    return 0;
}
/*
   The given description suggest that the array must have a peak (index where left & right side monotone decreasing)
   LET DP[i] = total height we can get | array satisfy the constraint
   DP[i] = A[i] * (i - nearest smaller element) + DP[nearest smaller element]
   Traverse the array left and right then we can get the answer --> max(DP[i])
*/