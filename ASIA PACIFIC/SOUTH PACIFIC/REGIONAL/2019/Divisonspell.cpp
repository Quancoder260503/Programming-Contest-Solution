#include "bits/stdc++.h" 
using namespace std; 
signed main(void)
{
    int n, m; 
    cin >> n >> m; 
    int ans = 0; 
    for(int i = 1; i <= n; i++)
    {
       string s; 
       cin >> s; 
       int good = 1;
       vector<int>cnt(26, 0);
       for(int j = 0; j < s.length(); j++)
       { 
          if(s[j] - 'A' + 1 > m)
          {
             good = 0; 
             break; 
          }
          cnt[s[j] - 'A']++; 
       }
       for(int j = 0; j < 26; j++)
       {
         good = good & (cnt[j] <= 1); 
       }
       ans += good; 
    }
    cout << ans << '\n';
    return 0;
}