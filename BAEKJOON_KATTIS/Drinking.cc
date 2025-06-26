#include "bits/stdc++.h"

using namespace std;

const int maxf = 2000;

int dyn[10][maxf][maxf], cc[maxf], dd[maxf]; 
string d[maxf];
int N, dr, c;
double C, D;

int doit(int i, int cost, int unit, vector<pair<int, int>>&T)
{
    if(i >= N)
    {
        if(unit == 0 && cost == 0)
        {
            for(auto [pos, amt] : T)
            {
                if(amt == 0) continue; 
                cout << d[pos] << " " << amt << '\n'; 
            }
            exit(0);
        }
        return 0; 
    }
    if(dyn[i][cost][unit] != -1) return dyn[i][cost][unit]; 
    int &ret = dyn[i][cost][unit];
    ret = 0; 
    for(int k = 0; cc[i] * k <= cost && dd[i] * k <= unit; k++)
    {
        T.push_back({i, k}); 
        ret |= doit(i + 1, cost - k * cc[i], unit - k * dd[i], T);
        T.pop_back(); 
    }
    return ret; 
}

int main(void)
{
    cin >> C >> D >> N; 
    c  = C * 100; 
    dr = D * 10 * 6;  
    for(int i = 0; i < N; i++)
    {
        string rate; 
        cin >> d[i] >> D >> rate >> C;
        cc[i] = C * 100;
        dd[i] = 60 * D / (rate[2] - '0'); 
    }
    memset(dyn, -1, sizeof(dyn)); 
    vector<pair<int, int>>T;
    doit(0, c, dr, T);  
    cout << "IMPOSSIBLE" << '\n'; 
    return 0;
}