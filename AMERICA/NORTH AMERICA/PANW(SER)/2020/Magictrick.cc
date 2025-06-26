#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    string S; 
    while (cin >> S)
    {
        vector<int>ctr(26); 
        for(int i = 0; i < S.length(); i++) ctr[S[i] - 'a']++; 
        int ret = 1; 
        for(int i = 0; i < 26; i++) ret = ret & (ctr[i] <= 1); 
        cout << ret << '\n'; 
    }
    return 0;
}