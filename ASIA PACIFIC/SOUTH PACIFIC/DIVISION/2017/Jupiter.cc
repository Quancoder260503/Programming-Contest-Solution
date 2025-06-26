#include "bits/stdc++.h"
using namespace std; 
signed main(void)
{
    int N, K, L, M;
    string A, B;
    while(cin >> N >> K >> L >> M >> A >> B)
    {
        vector<string>state = {"Alice", "Draw", "Bob"};
        auto stageD = [&](string S1, string S2)
        {
            int f1, f2; 
            f1 = f2 = 0; 
            for(int i = 0; i < K; i++)
            {
                if ((S1[i] == 'P' && S2[i] == 'R') || (S1[i] == 'R' && S2[i] == 'S') || (S1[i] == 'S' && S2[i] == 'P')) f1++;
                if ((S2[i] == 'P' && S1[i] == 'R') || (S2[i] == 'R' && S1[i] == 'S') || (S2[i] == 'S' && S1[i] == 'P')) f2++;
                if(f1 == M) return 0;
                if(f2 == M) return 2; 
            }
            return 1; 
        }; 
        auto stageC = [&](string S1, string S2)
        {
            int ret = 3; 
            for(int i = 0; i <= K - L; i++)
            {
                int j = i;
                string temp = S1;  
                while(j < i + L)
                {
                    if(S1[j] == 'R') temp[j] = 'P'; 
                    if(S1[j] == 'P') temp[j] = 'S'; 
                    if(S1[j] == 'S') temp[j] = 'R'; 
                    j++; 
                }
                ret = min(ret, stageD(temp, S2)); 
            } 
            return ret; 
        }; 
        auto stageB = [&](string S1, string S2)
        {
            int ret = 0; 
            for(int i = 0; i <= N - K; i++)
            {
                ret = max(ret, stageC(S1, S2.substr(i, K))); 
            } 
            return ret; 
        }; 
        auto stageA = [&](string S1, string S2) 
        {
            int ret = 3; 
            for(int i = 0; i <= N - K; i++)
            {
                ret = min(ret, stageB(S1.substr(i, K), S2)); 
            }
            return ret; 
        }; 
        cout << state[stageA(A, B)] << '\n'; 
    }
    return 0; 
}