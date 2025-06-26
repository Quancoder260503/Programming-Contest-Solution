#include "bits/stdc++.h"
using namespace std;
typedef long long Lint; 
signed main(void)
{
    int T;
    vector<int>     num   = {1, 2, 3, 4, 5, 6, 7, 8, 9, 
                             10, 20, 30, 40, 50, 60, 70, 80, 90, 
                             100, 200, 300, 400, 500, 600, 700, 800, 900,
                             1000};
    vector<string>  roman = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX",
                            "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC", 
                            "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM", 
                            "M"};
    reverse(num.begin(), num.end());
    reverse(roman.begin(), roman.end());
    auto get_roman = [&](int val, int &prefix)
    {
        string ret; 
        prefix = 0;
        int at = 0;
        while(val > 0)
        {
            while(val < num[at]) at++; 
            val = val - num[at]; 
            if(at == 0)
            {
                prefix++; 
            }
            else 
            {
                ret = ret + roman[at]; 
            }
        }
        return ret;
    };
    vector<string>ord; 
    int N = 1000; 
    int prefix = 0; 
    for(int i = 1; i < N; i++)
    {
        ord.push_back(get_roman(i, prefix));
    }
    sort(ord.begin(), ord.end()); 
    int at = 0; 
    while(at < ord.size() && ord[at] < "M") at++; 
    cin >> T;
    while(T--)
    {
        int N; 
        cin >> N;
        string ret = get_roman(N, prefix);
        if(ret.size() == 0)
        {
            cout << 1LL * (at + 1) * prefix << '\n'; 
        }
        else if(ret[0] < 'M')
        {
            cout << 1LL * (at + 1) * prefix + 1 + (lower_bound(ord.begin(), ord.end(), ret) - ord.begin()) << '\n'; 
        }
        else 
        {
            cout << -1LL * ((int)ord.size() - at) * prefix - (int)ord.size() + (lower_bound(ord.begin(), ord.end(), ret) - ord.begin()) << '\n';
        }
    }
    return 0; 
}
/*
   C D I L M X
*/