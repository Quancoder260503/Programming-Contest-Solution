#include "bits/stdc++.h"
using namespace std;
const int M = 1000;
signed main(void)
{
    string S;
    while (cin >> S)
    {
        if (S == "-1")
            break;
        if (S.size() == 1)
        {
            S = '1' + S;
            cout << S << '\n';
            continue;
        }
        auto rem = [&](string s, int num)
        {
            int ret = 0;
            int N = s.size();
            for (int i = 0; i < N; i++)
            {
                ret = ret * 10 + (s[i] - '0');
                ret = ret % num;
            }
            return (ret == 0);
        };
        auto div = [&](string s, int num)
        {
            string ret;
            int carry = 0;
            int N = s.size();
            for (int i = 0; i < N; i++)
            {
                carry = 10 * carry + (s[i] - '0');
                ret += ('0' + carry / num);
                carry = carry % num;
            }
            return ret;
        };
        auto chk = [&](string s)
        {
            for(int i = 0; i + 1 < s.size(); i++)
            {
                if(s[i] > '0') return false;
            }
            return true; 
        }; 
        string ret;
        for (int i = 9; i > 1; i--)
        {
            while (rem(S, i))
            {
                ret += ('0' + i);
                S = div(S, i);
            }
        }
        sort(ret.begin(), ret.end());
        if (chk(S))
        {
            cout << ret << '\n';
        }
        else
        {
            cout << "There is no such number." << '\n';
        }
    }
    return 0;
}
// greedily choosing the bignum first