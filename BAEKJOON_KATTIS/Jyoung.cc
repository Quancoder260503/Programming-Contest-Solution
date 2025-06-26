#include "bits/stdc++.h"
using namespace std;
#define MAXM 1024
#define MAXW 1024
int N, M, D, E;
int L[MAXM][MAXW], R[MAXW][MAXM];
int L2R[MAXM], R2L[MAXW];
int p[MAXM];
void stableMarriage()
{
    memset(R2L, -1, sizeof R2L);
    memset(p, 0, sizeof p);
    // Each man proposes...
    for (int i = 0; i < N; i++)
    {
        int man = i;
        while (man >= 0)
        { // propose until success
            int wom;
            while (1)
            {
                wom = L[man][p[man]++];
                if (R2L[wom] < 0 || R[wom][man] > R[wom][R2L[wom]])
                    break;
            }
            int hubby = R2L[wom];
            R2L[L2R[man] = wom] = man;
            man = hubby; // remarry the dumped guy
        }
    }
}

int main(void)
{
    while (cin >> N >> M >> D >> E)
    {
        vector<vector<int>> fplay(N, vector<int>(M, D + 1));
        vector<vector<int>> splay(N, vector<int>(M, D + 1));
        vector<pair<int, int>> ctoy(N, {0, -1});
        for (int i = 0; i < E; i++)
        {
            int T, U, V;
            cin >> T >> U >> V;
            --U, --V;
            if (V != -1)
                fplay[U][V] = min(fplay[U][V], T);
            auto c = ctoy[U];
            if (c.second != -1)
            {
                if (splay[U][c.second] == D + 1) splay[U][c.second] = 0;
                splay[U][c.second] += T - c.first;
            }
            ctoy[U] = {T, V};
        }
        if (N > M)
        {
            puts("impossible");
            continue;
        }
        for (int i = 0; i < N; i++)
            if (ctoy[i].second != -1)
            {
                if (splay[i][ctoy[i].second] == D + 1) splay[i][ctoy[i].second] = 0;
                splay[i][ctoy[i].second] += D - ctoy[i].first;
            }
        for (int i = 0; i < N; i++)
        {
            // printf("Player %d: \n", i + 1);
            // for(auto it : splay[i]) cout << it << ' ';
            vector<int> w(M);
            iota(w.begin(), w.end(), 0);
            auto cmp = [&](int a, int b)
            {
                return fplay[i][a] < fplay[i][b];
            };
            sort(w.begin(), w.end(), cmp);
            for (int j = 0; j < M; j++)
                L[i][j] = w[j];
        }
        for (int i = 0; i < M; i++)
        {
            vector<int> kd(N);
            iota(kd.begin(), kd.end(), 0);
            auto cmp = [&](int a, int b)
            {
                return splay[a][i] > splay[b][i];
            };
            sort(kd.begin(), kd.end(), cmp);
            for (int j = 0; j < N; j++)
                R[i][kd[j]] = j;
        }
        stableMarriage();
        for (int i = 0; i < N; i++)
            cout << L2R[i] + 1 << ' ';
        cout << '\n';
    }
    return 0;
}