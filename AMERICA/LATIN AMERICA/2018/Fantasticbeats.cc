#include "bits/stdc++.h"

using namespace std;
const int maxf = 1e3;

int g[maxf][maxf], st[maxf], ctr[maxf], in_cyc[maxf][maxf];
vector<int> path[maxf];

#define f first
#define s second

// CRT code from BENQ

pair<int64_t, int64_t> euclid(int64_t A, int64_t B)
{
    if (!B)
        return {1, 0};
    pair<int64_t, int64_t> p = euclid(B, A % B);
    return {p.s, p.f - A / B * p.s};
}
int64_t invGeneral(int64_t A, int64_t B)
{
    pair<int64_t, int64_t> p = euclid(A, B);
    assert(p.f * A + p.s * B == 1);
    return p.f + (p.f < 0) * B;
}

pair<int64_t, int64_t> CRT(pair<int64_t, int64_t> a, pair<int64_t, int64_t> b)
{
    //assert(0 <= a.f && a.f < a.s && 0 <= b.f && b.f < b.s);
    if (a.s < b.s)
        swap(a, b);
    int64_t x, y;
    tie(x, y) = euclid(a.s, b.s);
    int64_t g = a.s * x + b.s * y, l = a.s / g * b.s;
    if ((b.f - a.f) % g)
        return {-1, -1};
    x = (b.f - a.f) % b.s * x % b.s / g * a.s + a.f;
    return {x + (x < 0) * l, l};
}

int main(void)
{
    int B, Z;
    while (cin >> B >> Z)
    {
        for (int i = 1; i <= B; i++)
        {
            cin >> st[i];
            for (int j = 1; j <= Z; j++)
            {
                cin >> g[i][j];
            }
            for (int j = 1; j <= Z; j++)
                ctr[j] = 0;
            int at = st[i];
            while (!ctr[at])
            {
                path[i].push_back(at);
                ctr[at] = 1;
                at = g[i][at];
            }
            for (int j = 1; j <= Z; j++)
                ctr[j] = 0;
            at = st[i];
            while (ctr[at] < 3)
            {
                ctr[at]++;
                at = g[i][at];
            }
            for (int j = 1; j <= Z; j++)
            {
                ctr[j] = min(ctr[j], 2);
                if (ctr[j] == 2)
                    in_cyc[i][j] = 1;
            }
        }
        if (B == 1)
        {
            cout << st[1] << " " << 0 << '\n';
            break;
        }
        vector<int> targets;
        int pivot = 1;
        for (auto v : path[pivot])
        {
            int chk = 1;
            for (int j = pivot + 1; j <= B; j++)
            {
                int ok = 0;
                for (auto u : path[j])
                {
                    if (u == v)
                    {
                        ok = 1;
                        break;
                    }
                }
                chk = chk & ok;
            }
            if (chk)
                targets.push_back(v);
        }
        if (targets.size() == 0)
        {
            cout << "*" << '\n';
            break;
        }
        auto dist = [&](int idx, int at, int to)
        {
            int ret = 0;
            while (at != to)
            {
                ret++;
                at = g[idx][at];
            }
            return ret;
        };
        for (auto target : targets)
        {
            int all_cyc = 1;
            for (int i = 1; i <= B; i++)
            {
                all_cyc = all_cyc & (in_cyc[i][target]);
            }
            if (all_cyc)
            {
                int64_t M = dist(1, g[1][target], target) + 1;
                int64_t R = dist(1, st[1], target);
                for (int i = 2; i <= B; i++)
                {
                    int64_t M2 = dist(i, g[i][target], target) + 1;
                    int64_t R2 = dist(i, st[i], target) % M2;
                    auto ret = CRT({R, M}, {R2, M2});
                    R = ret.first;
                    M = ret.second;
                    if (R == -1)
                        break;
                }
                if (R != -1)
                {
                    cout << target << " " << R << '\n';
                    goto done;
                }
            }
            else
            {
                int chk = 1;
                vector<int> cyc, ncyc;
                for (int i = 1; i <= B; i++)
                {
                    if (!in_cyc[i][target])
                        ncyc.push_back(dist(i, st[i], target));
                    else
                        cyc.push_back(i);
                }
                for (int i = 1; i < ncyc.size(); i++)
                    chk = chk & (ncyc[i] == ncyc[i - 1]);
                if (chk)
                {
                    for (int i = 0; i < cyc.size(); i++)
                    {
                        int at = cyc[i];
                        int M = 1 + dist(at, g[at][target], target);
                        int R = dist(at, st[at], target);
                        // cout << ncyc[0] << " " << M << " " << R << '\n';
                        chk = chk & (ncyc[0] >= R && (ncyc[0] - R) % M == 0);
                    }
                    if (chk)
                    {
                        cout << target << " " << ncyc[0] << '\n';
                        goto done;
                    }
                }
            }
        }
        cout << "*" << '\n';
    done:;
    }
    return 0;
}