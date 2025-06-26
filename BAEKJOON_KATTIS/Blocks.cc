#include "bits/stdc++.h"
using namespace std;
const int M = 100;
signed main(void)
{
    int N, T;
    cin >> T;
    while (cin >> N)
    {
        int ret = INT32_MAX;
        for (int i = 1; i <= M; i++)
        {
            if(N % i == 0)
            {
                for (int j = 1; j <= N / i; j++)
                {
                    if( (N / i) % j == 0)
                    {
                        for (int k = 1; k <= N / i / j; k++)
                        {
                            if (i * j * k == N)
                            {
                                ret = min(ret, 2 * i * j + 2 * i * k + 2 * j * k);
                            }
                        }
                    }
                }
            }
        }
        cout << ret << '\n'; 
    }
    return 0;
}