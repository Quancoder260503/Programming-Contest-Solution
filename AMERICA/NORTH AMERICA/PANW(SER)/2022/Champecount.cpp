#include "bits/stdc++.h"
using namespace std; 
#define lint long long 
int n, mod;  
int digits(int x)
{
     return x == 0 ? 0 : 1 + digits(x / 10); 
}
lint binpow(int a, lint pow)
{
     lint ans = 1; 
     while(pow)
     {
         if(pow & 1) ans = ans % mod * a % mod; 
         a = a % mod * a % mod;
         pow = pow / 2; 
     }
     return ans; 
}
signed main(void)
{
    cin >> n >> mod; 
    lint tot = 0; 
    lint sum = 0;
    int ans = 0; 
    for(int i = 1; i <= n; i++)
    {
        vector<int>digit;
        int num = i;
        sum = sum % mod * binpow(10, digits(i)) % mod;  
        while(num)
        {
             digit.push_back(num % 10); 
             num = num / 10; 
        }
        //reverse(digit.begin(), digit.end()); 
        for(int j = 0; j < digit.size(); j++)
        {
             sum = (sum + digit[j] % mod * binpow(10, j) % mod ) % mod; 
        }
        ans += (sum == 0); 
    }
    cout << ans << '\n'; 
    return 0; 
}