#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n, d, cnt;
    cin >> n >> d;
    cnt = 0;  
    while (d >= n)
    {
        d = d - n; 
        n = n * 2;
        cnt++;  
    }
    cout << cnt << '\n'; 
    return 0;
}