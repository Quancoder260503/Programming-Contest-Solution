#include "bits/stdc++.h"
using namespace std;
#define lint long long
signed main(void)
{
    lint K;
    while (cin >> K)
    {
        string S = "SATELLITE";
        vector<lint> dyn(S.size() + 1);
        dyn[S.size()] = 1;
        vector<lint> tot;
        while (true)
        {
            for (int i = S.size() - 1; i >= 0; i--)
            {
                for (int j = 0; j < S.size(); j++)
                {
                    if(S[i] == S[j]) dyn[j] = min(K + 1, dyn[j] + dyn[j + 1]); 
                }
            }
            if(dyn[1] > K) break; 
            tot.push_back(dyn[1]); 
        }
        for(int i = tot.size() - 1; i >= 0; i--)
        {
            while(K >= tot[i])
            {
                cout << S[0]; 
                K = K - tot[i]; 
            }
            cout << S.substr(1, S.size()); 
        }
        cout << '\n'; 
    }
    return 0;
}