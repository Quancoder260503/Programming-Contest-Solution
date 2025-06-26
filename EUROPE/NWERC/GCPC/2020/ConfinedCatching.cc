#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N, x1, x2, y1, y2, x, y;
    cin >> N >> x1 >> y1 >> x2 >> y2;
    while (N--, cin >> x >> y)
    {
        if (y < y1)
            y1--;
        else if (y > y1)
            y1++;
        else if (x < x1)
            x1--;
        else if (x > x1)
            x1++;
        if (x < x2)
            x2--;
        else if (x > x2)
            x2++;
        else if (y < y2)
            y2--;
        else if (y > y2)
            y2++;
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << '\n';
    }
    return 0;
}