#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    string S;
    cin >> S;
    S = " " + S;
    int n = S.length();
    vector<vector<int>> pos(n, vector<int>(26, -1));
    for (int i = 1; i < n; i++)
    {
        vector<int>ctr(26, 0);
        ctr[S[i] - 'a']++; 
        for (int j = i - 1; j > 0; j--)
        {
            if(!ctr[S[j] - 'a']) pos[j][S[i] - 'a'] = i;
            ctr[S[j] - 'a']++; 
            if (S[i] == S[j]) break;
        }
    }
    int64_t ret = 0;
    for (int i = 1; i < n; i++) for (int j = 0; j < 26; j++)
    {
        ret += (pos[i][j] != -1);
    }
    cout << ret << '\n';
    return 0;
}