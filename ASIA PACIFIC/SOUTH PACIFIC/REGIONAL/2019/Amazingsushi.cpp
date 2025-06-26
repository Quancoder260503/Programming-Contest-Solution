#include "bits/stdc++.h"
using namespace std;
const int MAXN = 200; 
int n; 
int xa, ya, xb, yb;  
signed main(void)
{
    cin >> n;
    cin >> xa >> ya;
    cin >> xb >> yb; 
    int odd = 0; 
    int cur = 0;
    for(int i = 1; i <= n; i++)
    {
         int x; 
         cin >> x; 
         odd += (x & 1); 
         cur += x / 2;
    }
    int cura = cur, curb = cur;
    while(cura < xa)
    {
        cura++; 
        odd--; 
    }
    while(curb < xb)
    {
        curb++; 
        odd--;
    }
    while(odd && cura < ya)
    {
         cura++; 
         odd--; 
    }
    while(odd && curb < yb)
    {
        curb++;
        odd--;
    }
    if(cura > ya || curb > yb)
    {
        puts("No"); 
    }
    else if(odd != 0)
    {
        puts("No"); 
    }
    else 
    {
        puts("Yes"); 
    }
    return 0;
}