#include "bits/stdc++.h"
using namespace std;
const int MAXN = 1002;
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>ctr(MAXN); 
        for(int i = 0; i < N; i++)
        {
            int L, R; 
            cin >> L >> R; 
            for(int j = L; j <= R; j++) ctr[j]++;
        }
        int ret = -1; 
        for(int i = MAXN - 1; i > 0; i--)
        {
            if(ctr[i] == i)
            {
                ret = i; 
                break; 
            }
        }
        cout << ret << '\n'; 
    }
    return 0; 
}