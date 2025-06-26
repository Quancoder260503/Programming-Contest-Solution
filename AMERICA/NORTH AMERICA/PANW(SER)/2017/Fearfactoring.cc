#include "bits/stdc++.h" 

using namespace std;

#define int64_t unsigned long long

int main(void)
{
    int64_t a, b;
    while (cin >> a >> b)
    {
        auto f = [&](int64_t n)
        {
            int64_t ret = 0;
            for (int64_t left = 1, right = 0; left <= n; left = right + 1)
            {
                right = n / (n / left);
                ret += 1LL * (n / left) * (left + right) * (right - left + 1) / 2;
            }
            return ret;
        };
        cout << f(b) - f(a - 1) << '\n';
    }
    return 0;
}