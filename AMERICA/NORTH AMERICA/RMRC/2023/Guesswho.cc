#include "bits/stdc++.h"

using namespace std;

const int maxf = 10000;

int ret[maxf + 2];
char g[maxf][maxf];

int main(void)
{
    int N, M, Q;
    cin >> N >> M >> Q;
    memset(ret, 1, sizeof(ret));
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
        {
            cin >> g[i][j];
        }
    for (int i = 0; i < Q; i++)
    {
        int at;
        char state;
        cin >> at >> state;
        for (int j = 1; j <= N; j++)
            ret[j] &= (g[j][at] == state);
    }
    int ctr = 0;
    for (int i = 1; i <= N; i++)
        ctr += ret[i];
    if (ctr > 1)
    {
        cout << "ambiguous" << '\n'
             << ctr << '\n';
    }
    else
    {
        cout << "unique" << '\n';
        for (int i = 1; i <= N; i++)
            if (ret[i])
            {
                cout << i << '\n';
                break;
            }
    }
    return 0;
}