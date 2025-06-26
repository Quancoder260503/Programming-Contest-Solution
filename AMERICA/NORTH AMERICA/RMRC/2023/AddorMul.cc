#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 100;
const int mod = 1e9 + 7;

#define sz(x) (int)x.size()

const int B = (int)450;

int n, q, tc;
vector<string> s(2);

struct block
{
    bool add;
    int64_t l, sum, r;
};

block merge(const block &a, const block &b, const char op)
{
    if (op == '*')
    {
        if (a.add && b.add)
            return {true, a.l, (a.sum + 1LL * a.r * b.l % mod + b.sum) % mod, b.r};
        else if (a.add)
            return {true, a.l, a.sum, 1LL * a.r * b.sum % mod};
        else if (b.add)
            return {true, 1LL * a.sum * b.l % mod, b.sum, b.r};
        else
            return {false, 0, 1LL * a.sum * b.sum % mod, 0};
    }
    else
    {
        if (a.add && b.add)
            return {true, a.l, (a.sum + a.r + b.l + b.sum) % mod, b.r};
        else if (a.add)
            return {true, a.l, (a.sum + a.r) % mod, b.sum};
        else if (b.add)
            return {true, a.sum, (b.sum + b.l) % mod, b.r};
        else
            return {true, a.sum, 0, b.sum};
    }
}

block chunks[2][B];

void upd(int b)
{
    for (int i = 0; i < 2; i++)
    {
        block &c = chunks[i][b];
        c = {false, 0, 0, 0};
        int64_t acc = s[i][2 * b * B] - '0';
        for (int j = 1; j < B; j++)
        {
            char ops = s[i][2 * (b * B + j) - 1];
            int64_t v = s[i][2 * (b * B + j)] - '0';
            if (ops == '+')
            {
                if (!c.add)
                    c = {true, acc, 0, 0};
                else
                    c.sum = (c.sum + acc) % mod;
                acc = v;
            }
            else
                acc = 1LL * acc * v % mod;
        }
        if (c.add)
            c.r = (acc) % mod;
        else
            c.sum = acc;
    }
    return;
}

int64_t get_sum(int sign)
{
    block ret = chunks[sign][0];
    for (int i = 1; i < B; i++)
    {
        ret = merge(ret, chunks[sign][i], s[sign][2 * i * B - 1]);
    }
    return (ret.l + ret.sum + ret.r) % mod;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> q >> s[0];
    int sign = 0;
    s[1] = s[0];
    for (int i = 1; i < sz(s[1]); i += 2)
        s[1][i] = (s[0][i] == '+' ? '*' : '+');

    for (int i = 0; i < 2; i++)
    {
        while (sz(s[i]) < 2 * B * B)
            s[i] += "+0";
    }
    for (int i = 0; i < B; i++)
        upd(i);
    cout << get_sum(sign) << '\n';
    for (tc = 0; tc < q; tc++)
    {
        char q;
        cin >> q;
        if (q == 's')
        {
            int si, sj;
            cin >> si >> sj;
            --si, --sj;
            swap(s[0][2 * si], s[0][2 * sj]);
            swap(s[1][2 * si], s[1][2 * sj]);
            upd(si / B);
            upd(sj / B);
        }
        else if (q == 'a')
        {
            sign = sign ^ 1;
        }
        else
        {
            int u;
            cin >> u;
            s[0][2 * u - 1] = (s[0][2 * u - 1] == '+' ? '*' : '+');
            s[1][2 * u - 1] = (s[1][2 * u - 1] == '+' ? '*' : '+');
            upd((u - 1) / B);
        }
        cout << get_sum(sign) << '\n';
    }
    return 0;
}