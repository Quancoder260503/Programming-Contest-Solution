#include "bits/stdc++.h"

using namespace std; 

const int maxf = 1e5 + 2; 

const int INF = 1e9; 

int dyn[2][maxf][2]; 
int b[maxf]; 

int main(void)
{
    int N, B; 
    cin >> B >> N;  
    for(int i = 0; i < N; i++) cin >> b[N - 1 - i]; 
    for(int i = 0; i < 2; i++) for(int j = 0; j < maxf; j++) for(int k = 0; k < 2; k++)
    {
        dyn[i][j][k] = INF; 
    }
    dyn[0][0][0] = 0; 
    int M = N * B + 1; 
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                if(dyn[i & 1][j][k] < INF)
                {
                    //cout << dyn[i & 1][j][k] << '\n'; 
                    dyn[(i + 1) & 1][j + b[i] + k][0] = min(dyn[i & 1][j][k], dyn[(i + 1) & 1][j + b[i] + k][0]); 
                    dyn[(i + 1) & 1][j][1] = min(dyn[(i + 1) & 1][j][1], dyn[i & 1][j][k] + B - k - b[i]); 
                    dyn[i & 1][j][k] = INF; 
                }
            }
        }
    }
    int ret = INF; 
    for(int i = 0; i < M; i++) for(int j = 0; j < 2; j++)
    {
        if(dyn[N & 1][i][j] < INF)
        {
            ret = min(ret, max(i, dyn[N & 1][i][j])); 
        }
    }
    cout << ret << '\n'; 
    return 0; 
}