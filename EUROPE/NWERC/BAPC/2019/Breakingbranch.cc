#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        if(N % 2 == 0)
        {
            cout << "Alice" << "\n" << 1 << '\n'; 
        }
        else
        {
            cout << "Bob" << '\n'; 
        }
    }
    return 0; 
}