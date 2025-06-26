#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    string sa, sb;
    cin >> sa;
    cin >> sb;
    int ans = 0;
    auto chk = [&](string at)
    {
        int good = 1; 
        for(int i = 0; i < 4; i++)
        {
            good = good & (at[i] == sa[i] || at[i] == sb[i]); 
        }
        return good; 
    }; 
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int ii = 0; ii < 10; ii++)
            {
                for (int jj = 0; jj < 10; jj++)
                {
                    string at;
                    at += (char)(i + '0'); 
                    at += (char)(j + '0'); 
                    at += (char)(ii + '0'); 
                    at += (char)(jj + '0'); 
                    ans += chk(at); 
                }
            }
        }
    }
    cout << ans << '\n'; 
    return 0;
}