#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
using namespace std;
#define lint long long
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
lint rand(lint B)
{
    return (unsigned lint)rng() % B;
}
double time()
{
    return static_cast<double>(chrono::duration_cast<chrono::nanoseconds>(chrono::steady_clock::now().time_since_epoch()).count()) * 1e-9;
}
signed main(void)
{
    int n;
    cin >> n;
    vector<int> dx(n, 0);
    vector<int> dy(n, 0);
    int ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    set<pair<int, int>> dir;
    --ax, --ay, --bx, --by;
    for (int i = 0; i < n; i++)
    {
        cin >> dx[i] >> dy[i];
        dir.insert({dx[i], dy[i]});
    }
    function<bool(int, int, int, int)> chk;
    auto inside = [&](int r, int c)
    {
        return (0 <= r && r < n && 0 <= c && c < n);
    };
    chk = [&](int sx, int sy, int ex, int ey) -> bool
    {
        for (int i = 0; i < n; i++)
        {
            int px = sx + dx[i];
            int py = sy + dy[i];
            if (inside(px, py))
            {
                // cout << px << " " << py << " " << sx << " " << sy << " " << ex << " " << ey << '\n';
                if (px == ex && py == ey)
                    return true;
                if (dir.find({ex - px, ey - py}) != dir.end())
                    return true;
            }
        }
        return false;
    };
    if (chk(ax, ay, bx, by))
    {
        puts("Alice Wins");
    }
    else
    {
        double stime = time();
        while (time() - stime < 0.5)
        {

            lint tox = rand(n), toy = rand(n);
            if (tox == bx && toy == by)
                continue;
            if (chk(bx, by, tox, toy) == false)
            {
                printf("tie %lld %lld\n", tox + 1, toy + 1);
                return 0;
            }
        }
        puts("Bob Wins");
    }
    return 0;
}