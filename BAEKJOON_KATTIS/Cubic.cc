#include "bits/stdc++.h"
using namespace std;
template <int D, typename T>
struct Vec : public vector<Vec<D - 1, T>>
{
    static_assert(D >= 1, "Dimension must be positive");
    template <typename... Args>
    Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {}
};
template <typename T>
struct Vec<1, T> : public vector<T>
{
    Vec(int n = 0, T val = T()) : vector<T>(n, val) {}
};
const int M = 32;
signed main(void)
{
    int N;
    string S;
    while (cin >> S >> N)
    {
        Vec<3, int32_t> dyn(M, M, M, -1);
        function<int(int, int, int)> grundy;
        grundy = [&](int x, int y, int z) -> int
        {
            if(x < 1 || y < 1 || z < 1) return 0;
            if (dyn[x][y][z] != -1)
                return dyn[x][y][z];
            set<int> get_mex;
            for (int i = 0; i <= x / 2; i++)
            {
                for (int j = 0; j <= y / 2; j++)
                {
                    for (int k = 0; k <= z / 2; k++)
                    {
                        int ret = 0;
                        ret = ret xor grundy(i, j, k);
                        ret = ret xor grundy(x - i - 1, y - j - 1, z - k - 1);
                        ret = ret xor grundy(x - i - 1, y - j - 1, k);
                        ret = ret xor grundy(x - i - 1, j, z - k - 1);
                        ret = ret xor grundy(i, y - j - 1, z - k - 1);
                        ret = ret xor grundy(x - i - 1, j, k);
                        ret = ret xor grundy(i, y - j - 1, k);
                        ret = ret xor grundy(i, j, z - k - 1);
                        get_mex.insert(ret);
                    }
                }
            }
            int mex = 0;
            while (get_mex.count(mex))
                mex++;
            return dyn[x][y][z] = mex;
        };
        int32_t ret = 0;
        for (int _ = 0; _ < N; _++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            ret = ret xor grundy(x, y, z);
        }
        if (ret)
        {
            cout << S << '\n';
        }
        else
        {
            cout << (S == "ALBERT" ? "RUBEN" : "ALBERT") << '\n';
        }
    }
    return 0;
}