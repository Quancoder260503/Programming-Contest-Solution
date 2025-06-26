#include "bits/stdc++.h"
using namespace std;
const int MAXN = 1e5 + 10; 
vector<int64_t>H; 
map<int64_t, int> ctr;
int cnts[MAXN][10]; 
int add, en;
void doit(int id, int at, int64_t h_val)
{
    if (at == en)
    {
        ctr[h_val] += add;
        return;
    }
    for (int i = 0; i <= cnts[id][at]; i++)
    {
        doit(id, at + 1, h_val + 1LL * H[at] * i);
    }
    return;
};
signed main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    H.push_back(1); 
    for(int i = 0; i < 8; i++) H.push_back(H.back() * 9); 
    while(cin >> N >> K)
    {
        int id = 0;
        en = K; 
        for(int i = 0; i < N; i++)
        {
            char T; 
            cin >> T;
            if(T == 'C')
            {
                int amt; 
                cin >> amt; 
                for(int j = 0; j < amt; j++)
                {
                    int x;
                    cin >> x; 
                    cnts[id][--x]++; 
                }
                add = 1;
                doit(id++, 0, 0);
            }
            else if(T == 'J')
            {
                int amt;
                cin >> amt;
                vector<int>cnt(K);  
                for (int j = 0; j < amt; j++)
                {
                    int x;
                    cin >> x;
                    cnt[--x]++;
                }
                int64_t h_val = 0; 
                for(int j = 0; j < K; j++) h_val += cnt[j] * H[j];
                cout << ctr[h_val] << '\n'; 
            }
            else 
            {
               int at;
               cin >> at;
               add = -1; 
               doit(--at, 0, 0); 
            }
        }
    }
    return 0; 
}