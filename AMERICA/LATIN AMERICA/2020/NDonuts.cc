#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N;
    while (cin >> N)
    {
        auto get_num = [&](void)
        {
            string s, S;
            cin >> s;
            for (int i = 0; i < (int)s.length(); i++) if (isdigit(s[i])) S += s[i];
            int ret = 0;
            for (int i = 0; i < (int)S.length(); i++) ret += (S[i] - '0') * pow(10, (int)S.length() - i - 1);
            return ret;
        };
        int sum = get_num();
        int ret = 0;
        for (int i = 0; i < N; i++)
        {
            sum += get_num();
            ret += (sum % 100 != 0);
        }
        cout << ret << '\n';
    }
    return 0;
}