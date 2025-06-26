#include "bits/stdc++.h"

using namespace std;

int ctr[26];

int main(void)
{
    int N;
    cin >> N;
    vector<string> c;
    for (int i = 0; i < N; i++)
    {
        string S;
        cin >> S;
        c.push_back(S);
        ctr[S[0] - 'A']++;
    }
    for (int i = 0; i < N; i++)
    {
        int ret = 1;
        for (int j = 0; j < c[i].length(); j++)
        {
            ret = ret & (ctr[c[i][j] - 'A'] > 0);
        }
        if (ret)
        {
            puts("Y");
            return 0;
        }
    }
    puts("N");
    return;
}