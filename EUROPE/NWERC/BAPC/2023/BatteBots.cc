#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    long double c;
    cin >> c; 
    int ctr = 0; 
    while(c > 1.0)
    {
        ctr++;
        c = c / 2; 
    }
    cout << ctr + 1 << '\n'; 
    return 0; 
}