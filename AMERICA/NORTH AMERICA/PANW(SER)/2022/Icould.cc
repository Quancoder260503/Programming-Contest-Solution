#include "bits/stdc++.h"
using namespace std; 
int main(void)
{
    string S; 
    while(cin >> S)
    {
        int N = S.length();
        vector<int>ret;
        for(int k = 1; k <= N; k++)
        {
            vector<int>  ctr = {0, 0};
            vector<int> wctr = {0, 0}; 
            for (int j = 0; j < N; j++)
            {
                ctr[S[j] - 'A']++;
                if(ctr[0] == k)
                {
                    wctr[0]++; 
                    ctr[0] = ctr[1] = 0; 
                }
                else if(ctr[1] == k)
                {
                    wctr[1]++;
                    ctr[0] = ctr[1] = 0; 
                }
            }
            if(wctr[0] > wctr[1]) ret.push_back(k); 
        }  
        cout << ret.size() << '\n'; 
        for(auto it : ret) cout << it << " "; 
        cout << '\n'; 
    }
    return 0; 
}