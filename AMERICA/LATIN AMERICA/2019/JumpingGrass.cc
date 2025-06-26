#include "bits/stdc++.h"

using namespace std;
const int maxf = 2e5 + 4;

pair<int, int> tree[maxf << 2];
int arr[maxf];

pair<int, int> null = {-1, -1};

int N, Q;

void update(int pos, int l = 1, int r = N, int p = 1)
{
    if (l == r)
    {
        tree[p] = {arr[pos], pos};
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(pos, l, mid, 2 * p);
    else
        update(pos, mid + 1, r, 2 * p + 1);
    tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    return;
}

pair<int, int> query(int L, int R, int l = 1, int r = N, int p = 1)
{
    if (L > r || R < l)
        return null;
    if (L <= l && r <= R)
        return tree[p];
    int mid = (l + r) / 2;
    return max(query(L, R, l, mid, 2 * p), query(L, R, mid + 1, r, 2 * p + 1));
}

pair<int, int> findLeft(int val, int L, int R, int l = 1, int r = N, int p = 1)
{
    if (L > r || R < l || tree[p].first <= val)  return null;
    if (l == r) return tree[p]; 
    int mid = (l + r) / 2;
    auto ret = findLeft(val, L, R, mid + 1, r, 2 * p + 1);
    return (ret == null ? findLeft(val, L, R, l, mid, 2 * p) : ret);
}

pair<int, int> findRight(int val, int L, int R, int l = 1, int r = N, int p = 1)
{
    if (L > r || R < l || tree[p].first <= val) return null;
    if (l == r) return tree[p]; 
    int mid = (l + r) / 2;
    auto ret = findRight(val, L, R, l, mid, 2 * p);
    return (ret == null ? findRight(val, L, R, mid + 1, r, 2 * p + 1) : ret);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        update(i);
    }
    for (int i = 0; i < Q; i++)
    {
        char T;
        int at;
        cin >> T;
        if (T == 'U')
        {
            int val;
            cin >> at >> val;
            arr[at] = val;
            update(at);
        }
        else
        {
            cin >> at;
            pair<int, int> oret, ret;
            if (T == 'L')
                oret = findLeft(arr[at], 1, at - 1);
            else
                oret = findRight(arr[at], at + 1, N);
            if (oret == null)
            {
                cout << at << '\n';
            }
            else
            {
                auto L = query(1, at);
                auto R = query(at, N);
                if (L.first < R.first)
                {
                    ret = findRight(L.first, L.second + 1, N);
                }
                else
                {
                    ret = findLeft(R.first, 1, R.second - 1);
                }
                cout << ret.second << '\n';
            }
        }
    }
    return 0;
}