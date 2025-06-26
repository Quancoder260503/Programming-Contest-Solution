#include "bits/stdc++.h"
using namespace std;  
#define ldb long double 
#define TURN 48
ldb xa, ya, xb, yb, xc, yc; 
ldb xd, yd, xe, ye, xf, yf;
const ldb INF = 1e4;
ldb dist(ldb x, ldb y, ldb x2, ldb y2) 
{ 
    return (ldb) sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2)); 
}
ldb f(ldb x, ldb y)
{
     return dist(x, y, xa, ya) + dist(x, y, xb, yb) + dist(x, y, xc, yc); 
}
ldb findyF(ldb x)
{
     /*Ternary search on y*/
     ldb left = -INF, right = INF;
     for(int i = 1; i <= TURN; i++)
     {
        ldb y1 = (2 * left + right) / 3.0;
        ldb y2 = (left + 2 * right) / 3.0;
        if(f(x, y1) < f(x, y2)) right = y2;
        else left = y1; 
     } 
     return f(x, left);
}
ldb findxF()
{
     /*Ternary search on x*/ 
     ldb left = -INF, right = INF;
     for (int i = 1; i <= TURN; i++)
     {
        ldb x1 = (2 * left + right) / 3.0;
        ldb x2 = (left + 2 * right) / 3.0;
        if(findyF(x1) < findyF(x2)) right = x2; 
        else left = x1;
     }
     return findyF(left); 
}
ldb g(ldb x, ldb y)
{
     ldb tot = 0; 
     xc = x, yc = y; 
     xa = xd, ya = yd, xb = xe, yb = ye; 
     tot = max(tot, findxF());
     xa = xe, ya = ye, xb = xf, yb = yf; 
     tot = max(tot, findxF());
     xa = xf, ya = yf, xb = xd, yb = yd;
     tot = max(tot, findxF()); 
     return tot; 
}
ldb findy(ldb x)
{
    ldb left = -INF, right = INF;
    for(int i = 1; i <= TURN; i++)
    {
         ldb y1 = (2 * left + right) / 3.0;
         ldb y2 = (left + 2 * right) / 3.0; 
         if(g(x, y1) < g(x, y2)) right = y2; 
         else left = y1;
    }
    return g(x, left); 
}
ldb findx()
{
    ldb left = -INF, right = INF;
    for (int i = 1; i <= TURN; i++)
    {
         ldb x1 = (2 * left + right) / 3.0;
         ldb x2 = (left + 2 * right) / 3.0;
         if(findy(x1) < findy(x2)) right = x2; 
         else left = x1; 
    }
    return findy(left);
}
signed main(void)
{
    cin >> xd >> yd >> xe >> ye >> xf >> yf;  
    cout << setprecision(12) << findx() << '\n'; 
    return 0;
}
/*  
*/ 