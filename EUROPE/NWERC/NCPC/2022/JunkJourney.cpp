#include "bits/stdc++.h"
using namespace std;
#define MAXN 55
#define x first
#define y second
using pii = pair<int, int>;
#define mp make_pair
pii A[MAXN];
pii start, fin;
int n;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
string dir[4] = {"Right", "Left", "Up", "Down"};
set<pii> pos;
void go(int cur)
{
    start.x += dx[cur];
    start.y += dy[cur];
    cout << dir[cur] << '\n';
    if (pos.count(mp(start.x, start.y)))
    {
        int nx = start.x;
        int ny = start.y;
        while (pos.count(mp(nx, ny)))
        {
            nx += dx[cur];
            ny += dy[cur];
        }
        pos.erase(start);
        pos.insert(mp(nx, ny));
        pos.erase(mp(0, 0));
    }
    return;
}
void R() { go(0); }
void L() { go(1); }
void U() { go(2); }
void D() { go(3); }
signed main(void)
{
    scanf("%d", &n);
    scanf("%d %d %d %d", &start.x, &start.y, &fin.x, &fin.y);
    start.x -= fin.x;
    start.y -= fin.y;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &A[i].x, &A[i].y);
        A[i].x = A[i].x - fin.x;
        A[i].y = A[i].y - fin.y;
        pos.insert(mp(A[i].x, A[i].y));
    }
    while (start.x < 0)
        R();
    while (start.x > 0)
        L();
    while (start.y < 0)
        U();
    while (start.y > 0)
        D();
    while (pos.size())
    {
        int currx = pos.begin()->x;
        int curry = pos.begin()->y;
        if (currx != 0)
        {
            while (start.y < curry + 1)
                U();
            while (start.y > curry + 1)
                D();
            while (start.x > currx)
                L();
            while (start.x < currx)
                R();
            if (currx > 0)
            {
                R();
                D();
                while (start.x > 1)
                    L();
            }
            if (currx < 0)
            {
                L();
                D();
                while (start.x < -1)
                    R();
            }
        }
        else if (curry != 0)
        {
            R();
            while (start.y < curry)
                U();
            while (start.y > curry)
                D();
            if (curry > 0)
            {
                U();
                L();
            }
            if (curry < 0)
            {
                D();
                L();
            }
        }
        while (start.y < 0)
            U();
        while (start.y > 0)
            D();
        while (start.x < 0)
            R();
        while (start.x > 0)
            L();
    }
    return 0;
}
