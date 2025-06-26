#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int Ha, Hb, Xa, Xb, Ya, Yb;
    while(cin >> Ha >> Hb >> Xa >> Xb >> Ya>> Yb)
    {
        double ret = hypot(max({Xa - Ha, Ha - Ya, 0}), max({Xb - Hb, Hb - Yb, 0}));
        cout << fixed << setprecision(10) << ret << '\n';   
    }
    return 0; 
}