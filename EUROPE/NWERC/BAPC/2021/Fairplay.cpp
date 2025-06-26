#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define pii pair<int, int>
#define mp make_pair
int n;
signed main(void)
{
    cin >> n;
    if (n & 1)
    {
        puts("impossible");
        return 0;
    }
    else
    {
        lint atot = 0, btot = 0;
        vector<pii> arr;
        for (int i = 1; i <= n; i++)
        {
            int a, b;
            cin >> a >> b;
            atot += a, btot += b;
            arr.push_back(mp(a, b));
        }
        sort(arr.begin(), arr.end()); 
        atot = (atot * 2) / n;
        btot = (btot * 2) / n; 
        for(int i = 0; i < n / 2; i++)
        {
             if(arr[i].first + arr[n - i - 1].first != atot || arr[i].second + arr[n - 1 - i].second != btot)
             {
                puts("impossible");
                return 0;
             }
        }
        puts("possible"); 
    }
    return 0;
}