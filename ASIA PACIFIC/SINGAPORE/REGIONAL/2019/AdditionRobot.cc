#include "bits/stdc++.h"

using namespace std;

#define rep(i, j, k) for (int i = j; i < k; i++)

const int maxf = 1e5 + 2;
const int mod = 1e9 + 7;

template <class T, int N>
struct Matrix
{
    typedef Matrix M;
    array<array<T, N>, N> d{};
    M operator*(const M &m) const
    {
        M a;
        rep(i, 0, N) rep(j, 0, N) rep(k, 0, N) a.d[i][j] = (a.d[i][j] + d[i][k] % mod * m.d[k][j] % mod) % mod;
        return a;
    }
    vector<T> operator*(const vector<T> &vec) const
    {
        vector<T> ret(N);
        rep(i, 0, N) rep(j, 0, N) ret[i] = (ret[i] + d[i][j] % mod * vec[j] % mod) % mod;
        return ret;
    }
    M operator^(int64_t p) const
    {
        assert(p >= 0);
        M a, b(*this);
        rep(i, 0, N) a.d[i][i] = 1;
        while (p)
        {
            if (p & 1)
                a = a * b;
            b = b * b;
            p >>= 1;
        }
        return a;
    }
    friend ostream &operator<<(ostream &os, M p)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                os << p.d[i][j] << " ";
            }
            os << '\n';
        }
        return os;
    }
};

struct node
{
    int state = 0;
    Matrix<int64_t, 2> c;
    Matrix<int64_t, 2> rc;
    node operator+(const node &other)
    {
        node ret;
        ret.c = c * other.c;
        ret.rc = rc * other.rc;
        return ret;
    }
};
node tree[maxf << 2];

Matrix<int64_t, 2> na;
Matrix<int64_t, 2> nb;
node nc;

string S; 

void build(int l, int r, int p = 1)
{
    if (l == r)
    {
        char ch = S[l - 1]; 
        tree[p].state = 0;
        tree[p].c  = (ch == 'A' ? na : nb);
        tree[p].rc = (ch == 'A' ? nb : na);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * p);
    build(mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p + 1] + tree[2 * p];
    tree[p].state = 0;
}

void push(int p)
{
    if (tree[p].state)
    {
        swap(tree[2 * p].c, tree[2 * p].rc);
        swap(tree[2 * p + 1].c, tree[2 * p + 1].rc);
        tree[2 * p].state ^= tree[p].state;
        tree[2 * p + 1].state ^= tree[p].state;
        tree[p].state = 0;
    }
    return;
}

void update2(int L, int R, int l, int r, int p = 1)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        tree[p].state ^= 1;
        swap(tree[p].c, tree[p].rc);
        return;
    }
    int mid = (l + r) / 2;
    push(p);
    update2(L, R, l, mid, 2 * p);
    update2(L, R, mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p + 1] + tree[2 * p];
    return;
}

node query(int L, int R, int l, int r, int p = 1)
{
    if (L > r || R < l)
        return nc;
    if (L <= l && r <= R)
        return tree[p];
    int mid = (l + r) / 2;
    push(p);
    return query(L, R, mid + 1, r, 2 * p + 1) + query(L, R, l, mid, 2 * p);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    na.d[0][0] = na.d[0][1] = na.d[1][1] = nb.d[1][0] = nb.d[1][1] = nb.d[0][0] = 1;
    nc.c.d[0][0] = nc.c.d[1][1] = nc.rc.d[0][0] = nc.rc.d[1][1] = 1;
    cin >> S; 
    build(1, n); 
    for (int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r;
            update2(l, r, 1, n);
        }
        else
        {
            int l, r;
            int64_t a, b;
            cin >> l >> r >> a >> b;
            node mat = query(l, r, 1, n);
            int64_t reta = (mat.c.d[0][0] % mod * a % mod + mat.c.d[0][1] % mod * b % mod) % mod;
            int64_t retb = (mat.c.d[1][0] % mod * a % mod + mat.c.d[1][1] % mod * b % mod) % mod;
            cout << reta << " " << retb << '\n';
        }
    }
    return 0;
}