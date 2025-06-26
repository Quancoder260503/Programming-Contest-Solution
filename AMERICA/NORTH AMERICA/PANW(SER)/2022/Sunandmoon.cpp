#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e5 + 10
#define mp make_pair 
int ds, dm, ys, ym; 
signed main(void)
{
    cin >> ds >> ys >> dm >> ym; 
    for(int i = 1; i <= 5000; i++)
    {
        if((i + ds) % ys == 0 && (i + dm) % ym == 0)
        {
            cout << i << endl;
            return 0; 
        }
    }
    return 0;
}
