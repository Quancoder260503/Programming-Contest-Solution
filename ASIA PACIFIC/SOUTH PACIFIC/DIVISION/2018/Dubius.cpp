#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 3e5 + 10;
int n;
int arr[MAXN];
lint gcd(lint a, lint b)
{
    if(a == 0) return b;
    return gcd(b % a, a); 
}
signed main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    lint numer = 0, denom = 0, prefix = 0, acc = 0;
    for (int i = 1; i <= n; i++)
    {
        prefix += arr[i];
        numer += 1LL * i * prefix - acc; 
        acc += prefix; 
    }
    denom = 1LL * n * (n + 1) / 2; 
    cout << numer / gcd(numer, denom) << "/" << denom / gcd(numer, denom) << '\n'; 
    return 0;
}