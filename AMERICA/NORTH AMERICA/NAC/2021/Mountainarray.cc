#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    while (cin >> n)
    {
        vector<int>arr(n);
        for(int i = 0; i < n; i++)
        {
            cin >> arr[i]; 
        }
        int optL, optR;
        optL = optR = 0;
        vector<int>d(n); 
        for (int i = 0, l = 0, r = -1; i < n; i++)
        {
            int at = (i > r ? 1 : min(d[l + r - i], r - i + 1));
            while (0 <= i - at && i + at < n && arr[i - at] < arr[i - at + 1] && arr[i - at] == arr[i + at]) at++;
            if (2 * at - 1 > optR - optL + 1)
            {
                optR = i + at - 1;
                optL = i - at + 1;
            }
            d[i] = at--;
            if (i + at > r)
            {
                r = i + at;
                l = i - at;
            }
        }
        cout << (optL == 0 && optR == 0 ? -1 : optR - optL + 1) << '\n'; 
    }
    return 0;
}