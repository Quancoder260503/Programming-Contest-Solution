#include "bits/stdc++.h"

using namespace std;
const int maxf = 1e6 + 2; 

int ctr[maxf]; 

int main(void)
{
    int N, L, P;
    while (cin >> N >> L >> P)
    {
        vector<pair<int, int>>door; 
        for(int i = 0; i < N; i++)
        {
            door.push_back({i * L + L / 2, i + 1}); 
        }
        int ret = 0; 
        for(int i = 0; i < P; i++)
        {
            int x;
            cin >> x; 
            pair<int, int> at = {x, -1}; 
            int pos = lower_bound(door.begin(), door.end(), at) - door.begin(); 
            if(pos == door.size())
            {
                ctr[pos]++; 
                ret = max(ret, x - door[pos - 1].first); 
            }
            else if(pos == 0)
            {
                ctr[pos + 1]++; 
                ret = max(ret, door[pos].first - x); 
            }
            else 
            {
                if(door[pos].first - x > x - door[pos - 1].first)
                {
                    ctr[pos]++; 
                    ret = max(ret, x - door[pos - 1].first);
                }
                else 
                {
                    ctr[pos + 1]++; 
                    ret = max(ret, door[pos].first - x); 
                }
            }
        }
        int res = 0; 
        for(int i = 0; i < maxf; i++) res = max(res, ctr[i]); 
        cout << ret << "\n" << res << '\n'; 
    }
    return 0;
}