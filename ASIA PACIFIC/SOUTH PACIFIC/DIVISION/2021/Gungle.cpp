#include "bits/stdc++.h"
using namespace std;
char v[5] = {
    'A',
    'E',
    'I',
    'O',
    'U',
};
signed main(void)
{
    string s;
    cin >> s;
    int N = s.length();
    for (int i = 0; i < N; i++)
    {
        int good = 0;
        for (int j = 0; j < 5; j++)
        {
            good = good || (v[j] == s[i]);
        }
        if (good)
        {
            if (i == 0)
            {
                puts("no");
                return 0;
            }
            if (s[i - 1] == 'G' || s[i - 1] == 'L')
            {
                // Do nothing
            }
            else
            {
                puts("no");
                return 0;
            }
        }
    }
    puts("yes");
    return 0;
}