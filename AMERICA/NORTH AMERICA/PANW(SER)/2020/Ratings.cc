#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N, K; 
    while(cin >> N >> K)
    {
        double rata = 0, ratb = 0; 
        for(int i = 0; i < K; i++) 
        {
            int x;
            cin >> x;
            rata += x;
            ratb += x; 
        }
        rata += (N - K) * 3; 
        ratb += (N - K) * (-3); 
        cout << fixed << setprecision(10);
        cout << ratb / N << " " << rata / N << '\n'; 
    }
    return 0;
}