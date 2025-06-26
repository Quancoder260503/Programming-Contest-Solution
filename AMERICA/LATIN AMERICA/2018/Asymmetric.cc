#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10;

int gcd(int a, int b)
{
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main(void)
{
    long double N;
    while (cin >> N)
    {
        int n = round(N * 100);
        cout << 36000 / gcd(36000, n) << '\n';
    }
    return 0;
}