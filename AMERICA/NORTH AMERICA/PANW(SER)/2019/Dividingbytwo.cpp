#include "bits/stdc++.h"
using namespace std;
int a, b;
int f(int a, int b)
{
    if(a <= b) return b - a; 
    if(a & 1) return 1 + f(a + 1, b);
    return 1 + f(a / 2, b); 
}
signed main(void)
{
    cin >> a >> b;
    cout << f(a, b) << endl;
    return 0;
}