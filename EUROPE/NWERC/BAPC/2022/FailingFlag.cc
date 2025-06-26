#include "bits/stdc++.h"

using namespace std; 

int main(void)
{
    string dir = "NESW"; 
    auto get_angle = [&](string S)
    {
        int N = S.length(); 
        double ret = dir.find(S[N - 1]) * 90.0; 
        double ang = 90.0; 
        int sign = 1.0; 
        for(int i = N - 2; i >= 0; i--)
        {
            ang = ang * 0.5;
            if(S[i] != S[i + 1]) 
            {
                string c;
                c += S[i];  
                c += S[i + 1]; 
                if(c == "NW" || c == "WN")
                {
                    sign = (c == "NW" ? 1.0 : -1.0); 
                }
                else 
                {
                    sign = dir.find(S[i]) > dir.find(S[i + 1]) ? 1.0 : -1.0;
                } 
            }
            ret += ang * sign; 
        }
        return ret; 
    };
    string a, b; 
    cin >> a >> b; 
    double d1 = min(get_angle(b), get_angle(a)) , d2 = max(get_angle(a), get_angle(b)); 
    cout << fixed << setprecision(10) << min(d2 - d1, 360 - (d2 - d1)) << '\n';
    return 0; 
}