#include "bits/stdc++.h"
using namespace std;
#define double long double
#define TURN 200 
const double eps= 1e-7;
double xatm, yatm, xtar, ytar, L; 
double dist(double x, double y, double x2, double y2)
{
    return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
}
double f(double x, double y)
{
    return abs(dist(x, y, xatm, yatm) + dist(x, y, xtar, ytar) - L);   
}
pair<double, double> findyF(double x)
{
    /*Ternary search on y*/
    double left = yatm, right = ytar;
    for (int _ = 0; _ < TURN; _++)
    {
        double y1 = (2 * left + right) / 3.0;
        double y2 = (left + 2 * right) / 3.0;
        if (f(x, y1) < f(x, y2)) right = y2;
        else left = y1;
    }
    return {f(x, left), left};
}
pair<double, double> findxF(void)
{
    /*Ternary search on x*/
    double left = 0, right = xtar;
    for (int _ = 0; _ < TURN; _++)
    {
        double x1 = (2 * left + right) / 3.0;
        double x2 = (left + 2 * right) / 3.0;
        if (findyF(x1).first < findyF(x2).first) right = x2;
        else left = x1;
    }
    return {left, findyF(left).second};
}
int main(void)
{
    while(cin >> xtar >> ytar >> L)
    {
        cout << fixed << setprecision(7); 
        xatm = yatm = 0.0; 
        vector<pair<double, double>>ret; 
        ret.push_back({xatm, yatm});
        while(true)
        {
            auto curr = findxF();
            //cout << xatm << " " << yatm << " " << curr.first << " " << curr.second << " " << f(curr.first, curr.second) << '\n';
            if (f(curr.first, curr.second) < eps)
            {
                ret.push_back(findxF()); 
                ret.push_back({xtar, ytar}); 
                break; 
            }
            else 
            { 
                if(xatm == xtar)
                {
                    L = L - sqrt(1 + xtar * xtar); 
                    xatm = 0; 
                    yatm++; 
                }
                else if(xatm == 0)
                {
                    L = L - xtar; 
                    xatm = xtar;  
                }
                ret.push_back({xatm, yatm}); 
            }
        }
        cout << ret.size() << '\n';
        for(auto it : ret) cout << it.first << " " << it.second << '\n'; 
    }
}
/*
 */