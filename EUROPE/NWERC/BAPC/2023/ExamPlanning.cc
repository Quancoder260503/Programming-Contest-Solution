#include "bits/stdc++.h"

using namespace std;

const int maxf = 2500;

int64_t dyn[maxf][maxf];
int s[maxf], p[maxf], e[maxf], a[maxf];

int main(void)
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i] >> p[i] >> e[i] >> a[i];
    memset(dyn, -1, sizeof(dyn));
    dyn[0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
        {
            if(dyn[i - 1][j] != -1) 
            {
                dyn[i][j] = max(dyn[i][j], dyn[i - 1][j] + s[i] - e[i - 1]);
            }
            if (j > 0 && dyn[i - 1][j - 1] >= a[i - 1])
            {
                dyn[i][j] = max(dyn[i][j], dyn[i - 1][j - 1] + s[i] - p[i - 1] - a[i - 1]);
            }
        }
    int ret = 0;
    for (int i = 0; i <= n; i++)
    {
        if (dyn[n][i] == -1)
            continue;
        ret = max(ret, i);
        if (dyn[n][i] >= a[n])
            ret = max(ret, i + 1);
    }
    cout << ret << '\n';
    return 0;
}
/*
   dyn[i][j] = {maximum unit of time we can save if at the start of ith exams and passed j of them}
   dyn[i][j] = max(dyn[i][j], dyn[i - 1][j] + s[i] - e[i - 1]) 
   if(dyn[i - 1][j - 1] + s[i] - p[i - 1] >= a[i]) dyn[i][j] = max(dyn[i][j], dyn[i - 1][j - 1] + s[i] - p[i - 1] - a[i])
*/