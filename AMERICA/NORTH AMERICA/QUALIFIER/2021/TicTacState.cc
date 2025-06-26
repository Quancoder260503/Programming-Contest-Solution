#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int T, N;
    cin >> T;
    while (scanf("%o", &N) == 1)
    {
        vector<vector<int>> g(3, vector<int>(3, -1));
        int done = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                int id = 3 * i + j;
                if ((N >> id) & 1)
                {
                    g[i][j] = 0;
                }
                else
                {
                    done = 0;
                }
            }
        auto chk_win = [&](string state) -> int
        {
            for (int i = 0; i < 3; i++)
            {
                int chk = 1;
                for (int j = 1; j < 3; j++)
                    chk = chk & (state[i * 3 + j] == state[i * 3 + j - 1] && state[i * 3 + j] == 'X');
                if (chk)
                    return true;
            }
            for (int i = 0; i < 3; i++)
            {
                int chk = 1;
                for (int j = 1; j < 3; j++) chk = chk & (state[j * 3 + i] == state[(j - 1) * 3 + i] && state[j * 3 + i] == 'X');
                if (chk) return true;
            }
            int chk = 1;
            for (int i = 1; i < 3; i++)
            {
                chk = chk & (state[i * 4] == state[(i - 1) * 4] && state[i * 4] == 'X');
            }
            if (chk)
                return true;
            chk = 1;
            for (int i = 1; i < 3; i++)
            {
                chk = chk & (state[i * 2 + 2] == state[(i - 1) * 2 + 2] && state[i * 2 + 2] == 'X');
            }
            return chk;
        };
        int turn = (N >> 18) & 1;
        string state = ".........";
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (g[i][j] != -1)
                {
                    int id = 9 + 3 * i + j;
                    state[3 * i + j] = ((N >> id) & 1 ? 'X' : 'O');
                }
        if (chk_win(state))
        {
            cout << "X wins" << '\n';
            continue;
        }
        state = ".........";
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (g[i][j] != -1)
                {
                    int id = 9 + 3 * i + j;
                    state[3 * i + j] = ((N >> id) & 1 ? 'O' : 'X');
                }
        if (chk_win(state))
        {
            cout << "O wins" << '\n';
            continue;
        }
        cout << (done ? "Cat's" : "In progress") << '\n';
    }
    return 0;
}