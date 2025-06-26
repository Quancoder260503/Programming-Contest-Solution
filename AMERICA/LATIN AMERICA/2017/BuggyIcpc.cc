#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

int main(void)
{
    string s;
    cin >> s;
    vector<char> vowel = {'a', 'e', 'i', 'o', 'u'};
    vector<int> pos;
    int ctr = 0;
    for (int i = 0; i < sz(s); i++)
        for (int j = 0; j < 5; j++)
            if (s[i] == vowel[j])
            {
                ctr += 1;
                pos.push_back(i);
            }
    if (ctr == 0)
    {
        puts("1");
        return 0;
    }
    int flag = 0;
    for (int i = 0; i < 5; i++)
        if (s[0] == vowel[i])
        {
            flag = 1;
            break;
        }
    if (!flag)
    {
        puts("0");
    }
    else
    {
        if (ctr == 1)
        {
            cout << sz(s) << '\n';
            return 0;
        }
        int at = (ctr + 1) / 2;
        cout << pos[at] - pos[at - 1] << '\n';
    }
    return 0;
}