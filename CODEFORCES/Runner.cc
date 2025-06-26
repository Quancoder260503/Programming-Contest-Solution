#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int mod = 1e9 + 7;
struct matrix
{
    lint mat[3][3];
    void init()
    {
        memset(mat, 0, sizeof(mat));
    }
    void print()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << mat[i][j] << " ";
            }
            cout << '\n';
        }
    }
};
matrix operator*(const matrix &a, const matrix &b)
{
    matrix c;
    c.init();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                c.mat[i][j] = (c.mat[i][j] + mod + 1LL * a.mat[i][k] % mod * b.mat[k][j] % mod) % mod;
            }
        }
    }
    return c;
}
signed main(void)
{
    int n;
    lint m;
    while (cin >> n >> m)
    {
        vector<tuple<lint, int, int>> block;
        for (int i = 0; i < n; i++)
        {
            int a;
            lint L, R;
            cin >> a >> L >> R;
            --a;
            block.push_back({L, a, 1});
            block.push_back({R + 1, a, -1});
        }
        sort(block.begin(), block.end());
        auto exp = [&](lint pow, matrix a)
        {
            matrix c;
            c.init();
            for (int i = 0; i < 3; i++)
                c.mat[i][i] = 1;
            while (pow)
            {
                if (pow & 1) c = c * a;
                a = a * a;
                pow = pow / 2;
            }
            return c;
        };
        vector<lint> vis(3, 0);
        lint last = 1;
        matrix coef[8];
        for (int mask = 0; mask < 8; mask++)
        {
            coef[mask].init();
            if(mask & 1) coef[mask].mat[0][0] = coef[mask].mat[0][1] = 1;
            if(mask & 2) coef[mask].mat[1][0] = coef[mask].mat[1][1] = coef[mask].mat[1][2] = 1;
            if(mask & 4) coef[mask].mat[2][1] = coef[mask].mat[2][2] = 1;
        }
        matrix ret;
        ret.init();
        ret.mat[1][1] = 1;
        for (int i = 0; i < block.size(); i++)
        {
            int mask = 0; 
            int r    = get<1>(block[i]); 
            lint at  = get<0>(block[i]); 
            int p    = get<2>(block[i]); 
            for(int ii = 0; ii < 3; ii++)
            {
                mask = mask | ((vis[ii] == 0) << ii); 
            }
            if(at > last) ret = ret * exp(at - last, coef[mask]); 
            vis[r] += p; 
            last = at;  
        }
        ret = ret * exp(m - last, coef[(1 << 3) - 1]);
        cout << ret.mat[1][1] << '\n'; 
    }
    return 0;
}