#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int a, b, n; 
    cin >> a >> b >> n;
    int x = 0, y = b; 
    for(int i = 0; i < n + 1; i++)
    {
        int dx = 2 * a - x % (2 * a);  
        int dy = 2 * b - y % (2 * b);
        x = (x + min(dx, dy)) % (4 * a);
        y = (y + min(dx, dy)) % (4 * b);  
    }
    x = x - a; 
    y = y - b; 
    if(x > a)
    {
        x = 2 * a - x; 
    }
    if(y > b)
    {
        y = 2 * b - y; 
    }
    auto rec = [&](int &x, int &y)
    {
        int g = gcd(x, y);
        x = x / g;
        y = y / g; 
        return 0; 
    }; 
    rec(x, a);
    rec(y, b); 
    cout << x << " " << a << " " << y << " " << b << '\n'; 
    return 0; 
}