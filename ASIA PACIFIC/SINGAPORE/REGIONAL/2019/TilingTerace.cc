#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int maxf = 1e5 + 2;
const int maxb = 70;

int64_t dyn[maxf][maxb];

int main(void)
{
    int n, k, ga, gb, gc;
    string s;
    cin >> n >> k >> ga >> gb >> gc >> s;
    int ctr = 0;
    for (int i = 0; i < s.size(); i++) ctr += (s[i] == '#');
    memset(dyn, -1, sizeof(dyn));
    dyn[0][0] = 0;
    for (int i = 0; i < s.size(); i++)
        for (int j = 0; j < ctr + 1; j++)
        {
            if (dyn[i][j] == -1) continue;
            dyn[i + 1][j] = max(dyn[i + 1][j], dyn[i][j]);
            if (i + 1 < s.size() && s.substr(i, 2) == "..")
                dyn[i + 2][j] = max(dyn[i + 2][j], 1 + dyn[i][j]);
            if (i + 2 < s.size() && s.substr(i, 3) == ".#.")
                dyn[i + 3][j + 1] = max(dyn[i + 3][j + 1], dyn[i][j]);
        }
    int64_t ret = 0;
    for (int i = 0; i < ctr + 1; i++)
    {
        if (dyn[s.size()][i] == -1) continue;
        int tc = i, tb = dyn[s.size()][i], ta = min(k, n - tc * 3 - tb * 2 - (ctr - tc));
        if (ga > gb)
        {
            tb = tb * 2; 
            while (tb && ta + 1 <= k)
            {
                tb--;
                ta++;
            }
            tb = tb / 2; 
        }
        if (2 * ga > gb)
        {
            while (tb && ta + 2 <= k)
            {
                ta += 2;
                tb--;
            }
        }
        ret = max(ret, 1LL * ta * ga + 1LL * tb * gb + 1LL * tc * gc);
    }
    cout << ret << '\n';
    return 0;
}