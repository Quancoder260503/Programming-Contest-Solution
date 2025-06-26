#include "bits/stdc++.h" 
using namespace std; 
#define lint long long
int arr[20]; 
lint dp[10][20]; 
lint get(lint n)
{
     if(n <= 10)
     {
        return n;
     }
     vector<int>digits;
     memset(dp, 0, sizeof(dp));
     memset(arr, 0, sizeof(arr)); 
     while(n)
     {
        digits.push_back(n % 10); 
        n = n / 10; 
     }
     int N = (int) digits.size(); 
     reverse(digits.begin(), digits.end());
     arr[0] = 1; 
     for(int i = 1; i < digits.size(); i++)
     {
         arr[i] = arr[i - 1] && (digits[i] != digits[i - 1]); 
     }
     for(int i = 1; i < digits[0];  i++)
     {
        dp[i][0]++;
     }
     for(int i = 1; i < N; i++)
     {
         if(arr[i - 1])
         {
             for(int j = 0; j < digits[i]; j++)
             {
                 if(j != digits[i - 1])
                 {
                     dp[j][i]++;
                 }
             }
         }
         for(int j = 1; j <= 9; j++)
         {
            dp[j][i]++;
         }
         for(int j = 0; j <= 9; j++)
         {
            for(int k = 0; k <= 9; k++)
            {
                if(k == j) continue; 
                dp[j][i] += dp[k][i - 1]; 
            }
         }
     }
     lint ans = arr[N - 1]; 
     for(int i = 0; i <= 9; i++)
     {
        ans += dp[i][N - 1]; 
     }
     return ans; 
}
lint a, b; 
signed main(void)
{
    cin >> a >> b; 
    cout << get(b) - get(a - 1) << '\n'; 
    return 0; 
}