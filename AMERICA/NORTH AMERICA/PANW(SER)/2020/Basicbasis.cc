#include "bits/stdc++.h"
using namespace std;
const string HEX = "0123456789abcdef";
vector<int> operator^(const vector<int> &a, const vector<int> &b)
{
    int N = a.size();
    vector<int> ret(N);
    for (int i = 0; i < N; i++)
    {
        ret[i] = a[i] xor b[i];
    }
    return ret;
}
signed main(void)
{
    int n, m, K;
    while (cin >> n >> m >> K)
    {
        vector<vector<int>> basis(n + m);
        for (int i = 0; i < n + m; i++)
        {
            for (int j = 0; j < K; j++)
            {
                char ch;
                cin >> ch;
                int at = HEX.find(ch);
                for (int k = 3; k >= 0; k--)
                {
                    basis[i].push_back((at >> k) & 1);
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                basis[i] = min(basis[i], basis[i] ^ basis[j]);
            }
        }
        vector<int> zero(4 * K, 0);
        for (int i = n; i < n + m; i++)
        {
            if (basis[i] == zero)
            {
                int j = 0;
                for (; j < n && basis[j] != zero; j++);
                cout << (j < n ? j + 1 : -1) << '\n';
            }
            else
            {
                int ret = 0;
                for (int j = 0; j < n; j++)
                {
                    basis[i] = min(basis[i], basis[i] ^ basis[j]); 
                    if(basis[i] == zero)
                    {
                        cout << j + 1 << '\n'; 
                        ret = 1; 
                        break; 
                    }
                }
                if(ret == 1) continue; 
                cout << -1 << '\n'; 
            }
        }
    }
    return 0;
}