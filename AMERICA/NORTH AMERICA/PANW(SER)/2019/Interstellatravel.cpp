#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e5 + 10
#define mp make_pair
const double pi = acos(-1);
int n;
vector<pair<double, double> > arr;
signed main(void)
{
    cin >> n;
    double res = 0;
    double slope = 0;
    for (int i = 1; i <= n; i++)
    {
        double t, s, a;
        cin >> t >> s >> a;
        res += max(0.0, t - s * min(2 * pi - a, a));
        double pf = a + min(pi, t / s);
        double ps = a - min(pi, t / s);
        if (pf > 2 * pi)
        {
            pf = pf - 2 * pi;
            slope -= s; 
        }
        if (ps < 0)
        {
            slope += s;
            ps = ps + 2 * pi;
        }
        arr.push_back(mp(pf, s));
        arr.push_back(mp(a, -2 * s)); 
        arr.push_back(mp(ps, s));  
    }
    sort(arr.begin(), arr.end());
    double ans = res; 
    double x = 0; 
    for(int i = 0; i < arr.size(); i++)
    {
         res += slope * (arr[i].first - x);
         ans = max(ans, res); 
         slope += arr[i].second; 
         x = arr[i].first;
    }
    cout << fixed << setprecision(12) << ans << '\n'; 
    return 0;
}