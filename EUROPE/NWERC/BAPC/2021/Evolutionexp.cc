#include "bits/stdc++.h"
using namespace std;
string LCS(string a, string b)
{
    int N = a.length();
    a = " " + a; 
    b = " " + b; 
    vector<vector<int>>dyn(N + 1, vector<int>(N + 1)); 
    vector<vector<string>>str(N + 1, vector<string>(N + 1)); 
    for(int i = 1; i < N; i++) for(int j = 1; j < N; j++)
    {
        if(a[i] == b[j])
        {
            if(dyn[i][j] < dyn[i - 1][j - 1] + 1)
            {
                dyn[i][j] = dyn[i - 1][j - 1] + 1; 
                str[i][j] = str[i - 1][j - 1] + a[i]; 
            }
        }
        if(dyn[i][j] < dyn[i - 1][j])
        {
            dyn[i][j] = dyn[i - 1][j];
            str[i][j] = str[i - 1][j]; 
        }
        if(dyn[i][j] < dyn[i][j - 1])
        {
            dyn[i][j] = dyn[i][j - 1];
            str[i][j] = str[i][j - 1];
        }
    }
    return str[N - 1][N - 1]; 
}
const int maxf = 20; 
int main(void)
{
    int N; 
    while(cin >> N)
    {
        string A, B, ret;
        cin >> A >> B; 
        for(int i = 0; i < N; i += maxf)
        {
            string a = A.substr(i, min(maxf, N - i)); 
            string b = B.substr(i, min(maxf, N - i)); 
            ret += LCS(a, b); 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}