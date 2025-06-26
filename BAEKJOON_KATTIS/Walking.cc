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
signed main(void)
{ 
    int N, M; 
    while(cin >> N >> M)
    {
        vector<vector<char>>g(N + 1, vector<char>(M + 1)); 
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= M; j++)
            {
                cin >> g[i][j]; 
            }
        }
        Vec<4, int32_t>dyn(N + 2, M + 2, N + 2, M + 2, -1);
        function<int(int, int, int, int)>grundy; 
        grundy = [&](int sx, int sy, int ex, int ey) -> int
        {
            if(dyn[sx][sy][ex][ey] != -1) return dyn[sx][sy][ex][ey]; 
            set<int>get_mex;
            for(int i = sx; i <= ex; i++)
            {
                for(int j = sy; j <= ey; j++)
                {
                    if(g[i][j] == 'X') continue; 
                    int ret = grundy(sx, sy, i - 1, j - 1) xor grundy(i + 1, sy, ex, j - 1) xor grundy(sx, j + 1, i - 1, ey) xor grundy(i + 1, j + 1, ex, ey);
                    get_mex.insert(ret);  
                }
            }
            int mex = 0; 
            while(get_mex.count(mex)) mex++; 
            return dyn[sx][sy][ex][ey] = mex; 
        }; 
        cout << (grundy(1, 1, N, M) ? "First" : "Second") << '\n'; 
    }
    return 0; 
}