#include "bits/stdc++.h"

using namespace std;

const int maxf = 86400;

int prefix[maxf + 2]; 

int main(void)
{
    int N; 
    cin >> N; 
    for(int i = 0; i < N; i++)   
    {
        int M; 
        cin >> M; 
        for(int j = 0; j < M; j++)
        {
            int L, R; 
            cin >> L >> R; 
            prefix[L]++;
            prefix[R + 1]--;
        }
    }
    for(int i = 1; i < maxf; i++) prefix[i] += prefix[i - 1]; 
    pair<int, int>ret;
    for(int i = 0; i < maxf; i++)
    {
        if(ret.first < prefix[i]) ret = make_pair(prefix[i], 1);
        else if(ret.first == prefix[i]) ret.second++;
    }
    cout << ret.first << '\n' << ret.second << '\n'; 
    return 0; 
}