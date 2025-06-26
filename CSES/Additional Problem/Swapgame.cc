#include "bits/stdc++.h"
using namespace std;
const int dx[] = {0, 1, 2, 3, 4, 5, 1, 2, 4, 5, 7, 8};
const int dy[] = {3, 4, 5, 6, 7, 8, 0, 1, 3, 4, 6, 7};
signed main(void)
{
    // clock_t tStart = clock();
    int N = 9;
    string to = "123456789";
    string src;
    for (int i = 0; i < N; i++)
    {
        char ch;
        cin >> ch;
        src += ch;
    }
    queue<string> q;
    unordered_map<string, int> dist;
    q.push(src);
    dist[src] = 1;
    while (q.size())
    {
        string u = q.front();
        q.pop();
        int d = dist[u];
        for (int i = 0; i < 12; i++)
        {
            swap(u[dx[i]], u[dy[i]]);
            if (dist[u] == 0)
            {
                dist[u] = d + 1;
                q.push(u);
                if (u == to)
                    goto done;
            }
            swap(u[dx[i]], u[dy[i]]);
        }
    }
done:
    cout << dist[to] - 1 << '\n';
    return 0;
}