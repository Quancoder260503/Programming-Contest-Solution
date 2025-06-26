#include "bits/stdc++.h"

using namespace std;

const int maxb = 29;
const int maxf = 2e5 + 10;

struct Node
{
    int l, r;
    Node()
    {
        l = r = -1;
        return;
    }
};

namespace trie
{

    vector<Node> nodes;

    int new_node(void)
    {
        nodes.emplace_back();
        return (int)nodes.size() - 1;
    }

    void init(void)
    {
        nodes.clear();
        new_node();
    }

    void insert(int x, int bit)
    {
        int start = 0;
        for (int i = bit; i >= 0; i--)
        {
            if (x & (1 << i))
            {
                if (nodes[start].r == -1)
                    nodes[start].r = new_node();
                start = nodes[start].r;
            }
            else
            {
                if (nodes[start].l == -1)
                    nodes[start].l = new_node();
                start = nodes[start].l;
            }
        }
        return;
    }

    int query_min(int x, int bit)
    {
        int ret = 0;
        int start = 0;
        for (int i = bit; i >= 0; i--)
        {
            if (x & (1 << i))
            {
                if (nodes[start].r != -1)
                {
                    start = nodes[start].r;
                }
                else if (nodes[start].l != -1)
                {
                    start = nodes[start].l;
                    ret += (1LL << i);
                }
            }
            else
            {
                if (nodes[start].l != -1)
                {
                    start = nodes[start].l;
                }
                else if (nodes[start].r != -1)
                {
                    start = nodes[start].r;
                    ret += (1LL << i);
                }
            }
        }
        return ret;
    }
};

int a[maxf];

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    n = unique(a, a + n) - a;
    int64_t ret = 0;
    function<void(int, int, int)> dnc = [&](int l, int r, int bit)
    {
        if (l >= r)
            return;
        int m = 0, cost = INT32_MAX;
        trie::init();
        for (m = l; m <= r && !((a[m] >> bit) & 1); m++)
            trie::insert(a[m], bit);
        if (m == l || m == r + 1)
            return dnc(l, r, bit - 1);
        for (int i = m; i <= r; i++)
            cost = min(cost, trie::query_min(a[i], bit));
        ret += (cost == INT32_MAX ? 0 : cost);
        dnc(l, m - 1, bit - 1);
        dnc(m, r, bit - 1);
        return;
    };
    dnc(0, n - 1, maxb);
    cout << ret << '\n';
    return 0;
}