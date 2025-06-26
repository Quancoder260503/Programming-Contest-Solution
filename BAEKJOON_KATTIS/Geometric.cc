#include "bits/stdc++.h"
using namespace std;
int64_t N, M, mod;
vector<vector<int64_t>> get_product(vector<vector<int64_t>> &a, vector<vector<int64_t>> &b)
{
    vector<vector<int64_t>> ret(2, vector<int64_t>(2, 0));
    ret[0][0] = (a[0][0] % mod * b[0][0] % mod + a[0][1] % mod * b[1][0] % mod + mod) % mod;
    ret[1][0] = (a[1][0] % mod * b[0][0] % mod + a[1][1] % mod * b[1][0] % mod + mod) % mod;
    ret[0][1] = (a[0][0] % mod * b[0][1] % mod + a[0][1] % mod * b[1][1] % mod + mod) % mod;
    ret[1][1] = (a[1][0] % mod * b[0][1] % mod + a[1][1] % mod * b[1][1] % mod + mod) % mod;
    return ret;
}
int main(void)
{
    while (cin >> N >> M >> mod)
    {
        vector<vector<int64_t>>mat  = {{1 % mod, 0}, {1 % mod, 0}};
        vector<vector<int64_t>>base = {{N % mod, 1}, {0, 1 % mod}};
        M--; 
        while(M)
        {
            if(M & 1) mat = get_product(base, mat);
            M = M / 2; 
            base = get_product(base, base); 
        } 
        cout << mat[0][0] << '\n'; 
    }
    return 0;
}