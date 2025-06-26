#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 2;

int prefix[maxf]; 

int main(void)
{
    int N, P, D;
    string S; 
    cin >> N >> P >> D >> S; 
    S = " " + S + S; 
    for(int i = 1; i <= 2 * N; i++)
    { 
        prefix[i] = prefix[i - 1] + (S[i] == 'Z'); 
    }
    int ret = 0; 
    for(int l = 1, r = P; l <= N; l++, r++)
    {
        ret += (prefix[r] - prefix[l - 1] < D); 
    }
    cout << ret << '\n'; 
    return 0; 
}