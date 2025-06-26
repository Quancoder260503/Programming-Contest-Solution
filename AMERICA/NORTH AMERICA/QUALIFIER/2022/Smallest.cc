#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int A, B, C; 
    while (cin >> A >> B >> C)
    {
        int32_t ret = INT32_MAX;
        if(A + B + C >= 0)
        {
            ret = A + B + C; 
        }
        if(A + B - C >= 0)
        {
            ret = min(ret, A + B - C); 
        }
        if(A - B + C >= 0) 
        {
            ret = min(ret, A - B + C); 
        }
        if(A - B - C >= 0)
        {
            ret = min(ret, A - B - C); 
        }
        if(A - B >= 0 && (A - B) % C == 0)
        {
            ret = min(ret, (A - B) / C); 
        }
        if(A - B >= 0 && (A - B) * C >= 0)
        {
            ret = min(ret, (A - B) * C); 
        }
        if((A + B) % C == 0)
        {
            ret = min(ret, (A + B) / C); 
        }
        if((A + B) * C >= 0)
        {
            ret = min(ret, (A + B) * C); 
        }
        if(A % B == 0 && (A / B) * C >= 0)
        {
            ret = min(ret, (A / B) * C); 
        }
        if(A % B == 0 && (A / B) % C == 0)
        {
            ret = min(ret, (A / B) / C); 
        }
        if(A * B * C >= 0)
        {
            ret = min(ret, A * B * C); 
        }
        if((A * B) % C == 0)
        {
            ret = min(ret, (A * B) / C);
        }
        if(A % B == 0 && (A / B) + C >= 0)
        {
            ret = min(ret, (A / B) + C); 
        }
        if(A % B == 0 && (A / B) - C >= 0)
        {
            ret = min(ret, (A / B) - C); 
        }
        if(A * B - C >= 0)
        {
            ret = min(ret, A * B - C); 
        }
        if(A * B + C >= 0)
        {
            ret = min(ret, A * B + C); 
        }
        cout << ret << '\n'; 
    }
    return 0;
}