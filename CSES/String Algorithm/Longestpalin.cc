#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    string S;
    while (cin >> S)
    {
        int N = S.length();
        vector<int> oddd(N);
        vector<int> even(N);
        int optL, optR;
        optL = optR = 0;
        for (int i = 0, l = 0, r = -1; i < N; i++)
        {
            int at = (i > r ? 1 : min(oddd[l + r - i], r - i + 1));
            while (0 <= i - at && i + at < N && S[i - at] == S[i + at]) at++;
            if (2 * at - 1 > optR - optL + 1)
            {
                optR = i + at - 1;
                optL = i - at + 1;
            }
            oddd[i] = at--;
            if (i + at > r)
            {
                r = i + at;
                l = i - at;
            }
        }
        for (int i = 0, l = 0, r = -1; i < N; i++)
        {
            int at = (i > r ? 0 : min(even[l + r - i + 1], r - i + 1));
            while (0 <= i - at - 1 && i + at < N && S[i - at - 1] == S[i + at]) at++;
            if (2 * at > optR - optL + 1)
            {
                optR = i + at - 1;
                optL = i - at;
            }
            even[i] = at--;
            if (i + at > r)
            {
                r = i + at;
                l = i - at - 1;
            }
        }
        for (int i = optL; i <= optR; i++)
        {
            cout << S[i];
        }
    }
    return 0;
}