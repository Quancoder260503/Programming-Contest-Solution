#include "bits/stdc++.h" 
using namespace std; 
signed main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<int>H(N); 
        for(int i = 0; i < N; i++) cin >> H[i]; 
        vector<int>lds; 
        vector<vector<int>>ret; 
        for(int i = 0; i < N; i++)
        {
            int pos = upper_bound(lds.begin(), lds.end(), -H[i]) - lds.begin(); 
            if(pos == lds.size())
            {
                ret.push_back({-H[i]}); 
                lds.push_back(-H[i]); 
            }
            else 
            {
                lds[pos] = -H[i]; 
                ret[pos].push_back(-H[i]); 
            }
        }
        cout << ret.size() << '\n'; 
        for(int i = 0; i < ret.size(); i++)
        {
            for(auto it : ret[i])
            {
                cout << -it << " "; 
            }
            cout << '\n'; 
        }
    }
    return 0; 
}