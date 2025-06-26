#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    int n; 
    cin >> n; 
    for(int i = 0; i < n; i++)
    { 
        double h, g, w, p; 
        cin >> w >> g >> h >> p; 
        h = h - p, g = g - p; 
        double l = 0.0;
        double r = w; 
        auto f = [&](double x)
        {
            return sqrt(h * h + x * x) + sqrt(g * g + (w - x) * (w - x)); 
        }; 
        for(int _ = 0; _ < 1000; _++)
        {
            double x1 = (2 * l + r) / 3.0; 
            double x2 = (l + 2 * r) / 3.0; 
            if(f(x1) < f(x2)) r = x2;
            else l = x1; 
        }
        double ret = sqrt(w * w + (g - h) * (g - h)); 
        cout << fixed << setprecision(10) << ret << " " << f(l) << '\n'; 
    }
    return 0;
}
