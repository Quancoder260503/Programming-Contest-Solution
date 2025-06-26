#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N; 
    string S; 
    while(cin >> S >> N)
    {
        if(N % 5 == 2 || N % 5 == 0)
        {
            cout << "Hanako" << '\n'; 
        }
        else 
        {
            cout << "Taro" << '\n'; 
        }
    }
    return 0;
}
/*
*/