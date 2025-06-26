#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    string S;
    getline(cin, S);  
    int ans = 0;
    if(S.length() == 0) return 0;
    for (int i = 0; i < S.length(); i++)
    {
        ans += (int)S[i];
    }
    ans = ans / (S.length()); 
    cout << (char) ans << '\n'; 
    return 0;
}