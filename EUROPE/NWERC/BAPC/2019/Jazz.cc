#include "bits/stdc++.h"
using namespace std;
const int M = 1e5 + 10;
signed main(void)
{
    int N;
    while (cin >> N)
    {
        int ret = 1;
        int num = N;
        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0)
            {
                int cnt = 0;
                while (num % i == 0)
                {
                    cnt++;
                    num = num / i;
                }
                if (cnt % 2 == 0)
                {
                    ret = ret * i;
                }
            }
        }
        if (ret == 1)
        {
            for (int i = 2; i < M; i++)
            {
                if (gcd(i, N) == 1)
                {
                    ret = ret * i;
                    break;
                }
            }
        }
        cout << ret << '\n';
    }
    return 0;
}