#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 2; 
int h[maxf], W, H; 

int main(void)
{
    cin >> W >> H;
    for(int i = 1; i <= W; i++) cin >> h[i]; 
    int g = 0; 
    for(int i = 1; i <= W; i++)
    {
        int x = H - h[i];
        if(x < g)
        {
            cout << "impossible" << '\n'; 
            return 0; 
        }
        if(x % 2 == g % 2) g = max(0, g - 1); 
        else g++; 
    }
    cout << (g == 0 ? "" : "im") << "possible" << '\n'; 
    return 0;
}