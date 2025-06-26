#include "bits/stdc++.h"

using namespace std; 
const int maxf = 3e5 + 2; 

int vis[maxf]; 
double pret[maxf], pstuck[maxf]; 

int main(void)
{
    int L, P; 
    cin >> L >> P; 
    for(int i = 0; i < L; i++)
    {
        cin >> pret[i]; 
    }
    for(int i = L; i < L + P; i++)
    {
        double pleft, pright;
        int left, right; 
        cin >> pleft >> pright >> left >> right; 
        --left, --right; 
        pret[i]   = pret[left] * pleft + pret[right] * pright; 
        pstuck[i] = pstuck[left] * pleft + pstuck[right] * pright + (1.0 - pleft - pright);  
        vis[left] = vis[right] = 1; 
    }
    double ret = 0; 
    for(int i = 0; i < L + P; i++)
    {
        if(!vis[i])
        {
            ret = max(ret, pret[i] / (1.0 - pstuck[i]));
            // cout << i << " " << pret[i] / (1.0 - pstuck[i]) << '\n';  
        }
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}