#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    string A, B; 
    while(cin >> A >> B)
    {
        string S = A + B; 
        sort(S.begin(), S.end()); 
        cout << S << '\n'; 
    }
    return 0; 
}