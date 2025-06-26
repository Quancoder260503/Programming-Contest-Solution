#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    string S; 
    while(cin >> S)
    {
        int n = S.length();
        int curr = S[0]; 
        vector<int64_t>coef; 
        int sign = (S[0] == 'H' ? -1 : 1); 
        for(int i = 1; i < n; i++) if(curr != S[i])
        {
            coef.push_back(2 * i + 1); 
            curr = S[i]; 
        }
        vector<int64_t>ret{-1, 0}; 
        for(int i = 0; i < coef.size(); i++)
        {
            vector<int64_t>curr = {-coef[i], 1};  
            vector<int64_t>tmp(ret.size() + 1, 0); 
            for(int j = 0; j < ret.size(); j++) for(int k = 0; k < curr.size(); k++)
            {
                tmp[j + k] += 1LL * ret[j] * curr[k]; 
            }
            sign = -sign; 
            ret = tmp;
        }
        cout << coef.size() << '\n'; 
        int id = 0; 
        for(int j = ret.size() - 1; j >= 0; j--) if(ret[j] != 0) 
        {
            id = j;
            break; 
        }
        for(int i = id; i >= 0; i--) cout << ret[i] * sign << " "; 
        cout << '\n'; 
    }
    return 0;
}
