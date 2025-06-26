#include "bits/stdc++.h"
using namespace std;
#define int64_t long long
int main(void)
{
    int64_t S, T;  
    while(cin >> T >> S)
    {
        int64_t num = 2 * (T + 1) * T + 1; 
        int64_t den = 0; 
        for(int64_t i = 0; i <= S; i++)
        {
            den += min(i, (S - i) * 2) + 1;
            den += max(0LL, (2 * S - i) / 2 - i); 
        }
        den = (den - S - 1) * 4 + 1;
        for(int64_t i = 0; i <= T; i++)
        {
            num -= max(0LL, -max(0LL, (S - i) * 2) + min(i, T - i)) * 4;
            num -= max(0LL, -max(0LL, (S - i) * 2) + min(i - 1, T - i)) * 4; 
        } 
        num = num - (T > S ? 4 * (T - S) : 0); 
        if(num >= den) cout << 1 << '\n';
        else cout << num / gcd(num, den) << "/" << den / gcd(num,den) << '\n'; 
    }
    return 0; 
}