#include "bits/stdc++.h"
using namespace std;
int n, k;
signed main(void)
{
    cin >> n;
    vector<int> cntY(3, 0);
    vector<int> cntN(3, 0);
    int totx, toty;
    totx = toty = 0;
    for (int i = 0; i < n; i++)
    {
        char s;
        cin >> s;
        char ch, ch2, ch3;
        cin >> ch >> ch2 >> ch3;
        if (s == 'Y')
        {
            totx++;
            cntY[0] += (ch == 'Y');
            cntY[1] += (ch2 == 'Y');
            cntY[2] += (ch3 == 'Y');
        }
        else
        {
            toty++;
            cntN[0] += (ch == 'Y');
            cntN[1] += (ch2 == 'Y');
            cntN[2] += (ch3 == 'Y');
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (cntY[i] * toty >= cntN[i] * totx)
        {
            puts("Not Effective");
        }
        else
        {
            cout << fixed << setprecision(10) << (1.0 - (1.0 * cntY[i] * toty) / (1.0 * cntN[i] * totx)) * 100.0 << '\n';
        }
    }
    return 0;
}