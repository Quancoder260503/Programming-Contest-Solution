#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int n;
    cin >> n;
    map<string, double> dyn;
    dyn["pink"] = 0.0;
    for (int i = 0; i < n; i++)
    {
        string u, v;
        double cost;
        cin >> u >> v >> cost;
        if(!dyn.count(v)) continue; 
        if (dyn.count(u))
        {
            dyn[u] = max(dyn[u], dyn[v] + log2(cost));
        }
        else
        {
            dyn[u] = dyn[v] + log2(cost);
        }
    }
    if(dyn.count("blue") == 0)
    {
        cout << 0 << '\n';
        return 0;
    }
    if (dyn["blue"] > log2(10))
    {
        cout << fixed << setprecision(10) << (10) << '\n';
    }
    else
    {
        dyn["blue"] = pow(2, dyn["blue"]);
        cout << fixed << setprecision(10) << dyn["blue"] << '\n';
    }
    return 0;
}