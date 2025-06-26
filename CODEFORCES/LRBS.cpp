#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 1e6 + 10
#define mp make_pair
#define pii pair<int,int>
int n; 
char s[MAXN]; 
int dp[MAXN]; 
signed main(void)
{
    scanf(" %s", &s); 
    n = strlen(s); 
    stack<int>stk; 
    pii ans = mp(0, 0);
    for(int i = 0; i < n; i++)
    {
        if(s[i] == '(')
        {
             stk.push(i); 
        }
        else 
        {
             if(stk.size())
             { 
                dp[i] = i - stk.top() + 1 + (stk.top() > 0 ? dp[stk.top() - 1] : 0);
                stk.pop();     
             }
             if(dp[i] == ans.first)
             {
                 ans.second++; 
             }
             else if(dp[i] > ans.first)
             {
                 ans.first = dp[i]; 
                 ans.second = 1; 
             }

        }
    }
    printf("%d %d\n", ans.first, ans.first == 0 ? 1 : ans.second); 
    return 0;
}