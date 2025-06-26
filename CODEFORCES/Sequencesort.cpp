#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e6 + 10 
const int INF = 1e9;
int n;
void solve()
{
     cin >> n; 
     vector<int>arr(n); 
     vector<int>L(n, INF); 
     vector<int>R(n, -INF); 
     vector<int>cor;
     for(int i = 0; i < n; i++)
     {
         cin >> arr[i]; 
         arr[i]--;
         cor.push_back(arr[i]);
         L[arr[i]] = min(L[arr[i]], i); 
         R[arr[i]] = max(R[arr[i]], i);  
     }
     sort(cor.begin(), cor.end());
     cor.erase(unique(cor.begin(), cor.end()), cor.end()); 
     reverse(cor.begin(), cor.end()); 
     int N = cor.size(); 
     vector<int>dp(N, 1); 
     for(int i = 0; i + 1 < N; i++)
     {
         if(L[cor[i]] > R[cor[i + 1]])
         {
             dp[i + 1] = dp[i] + 1; 
         }
     } 
     int ans = 0; 
     for(int i = 0; i < N; i++)
     {
         ans = max(ans, dp[i]); 
     }
     cout << N - ans << '\n'; 
     return; 
} 
signed main(void)
{
    int t; 
    cin >> t;
    while(t--)
    {
         solve(); 
    }
    return 0; 
}