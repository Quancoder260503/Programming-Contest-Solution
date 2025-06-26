#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    string S; 
    while(cin >> S)
    {
        int n = S.length(); 
        for(int i = 0; i < n; i++) if(S[i] == '(')
        {
            cout << (i == n - i - 2 ? "correct" : "fix") << '\n'; 
            break; 
        }
    }
    return 0;
}