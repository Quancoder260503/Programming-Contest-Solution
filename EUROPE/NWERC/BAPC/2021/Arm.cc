#include "bits/stdc++.h" 
using namespace std;
signed main(void) 
{
    int X, Y, R; 
    while(cin >> X >> Y >> R)
    {
        cout << X + R << " " << Y + R << '\n'; 
        cout << X - R << " " << Y + R << '\n'; 
        cout << X - R << " " << Y - R << '\n';
        cout << X + R << " " << Y - R << '\n'; 
    }
    return 0;
}