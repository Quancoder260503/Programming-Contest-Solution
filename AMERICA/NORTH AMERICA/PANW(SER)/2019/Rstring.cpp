#include "bits/stdc++.h"
using namespace std; 
int a[26]; 
string s;
const int mod = 11092019; 
signed main(void)
{
     cin >> s;
     long long ans = 1;  
     for(int i = 0; i < s.length(); i++)
     { 
        a[s[i] - 'a']++; 
     }
     for(int i = 0; i < 26; i++)
     {
         ans = ans % mod * (a[i] + 1) % mod; 
     }
     cout << ans << '\n';
     return 0; 
}