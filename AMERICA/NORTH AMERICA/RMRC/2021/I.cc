#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
#define lint long long
int n;
lint c;
lint pf[MAXN];
lint arr[MAXN];
lint acc[MAXN]; 
signed main(void)
{
    cin >> n >> c;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        pf[i] = pf[i - 1] + arr[i];
    }
    int s, e;
    s = e = 1;
    while (s <= n)
    {
        if (e + 1 > n)
            s++;
        else if (pf[e + 1] - pf[s - 1] > c)
        {
            s++;
        }
        else
        {
            e++;
        }
        acc[s]++; 
        acc[e + 1]--; 
    }
    for(int i = 1; i <= n; i++)
    {
        acc[i] += acc[i - 1];
        cout << acc[i] + (i == 1) << '\n'; 
    }
    return 0;
}