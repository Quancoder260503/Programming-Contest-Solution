#include "bits/stdc++.h"

using namespace std;

#define double long double

const int maxf = 2e5 + 2;

double ev[maxf], dyn[maxf];

// ev[i] * (1 - P) = ev[i - 1] + 1 + P * R

int main(void)
{
    int N, T, R;
    double P;
    cin >> N >> T >> R >> P;
    for (int i = 1; i <= N; i++)
    {
        ev[i] = (ev[i - 1] + 1 + P * R) / (1.0 - P); 
    }
    for (int i = 1; i <= N; i++)
    {
        dyn[i] = ev[i]; 
        for (int j = 0; j < i; j++)
        {
            dyn[i] = min(dyn[i], dyn[j] + T + ev[i - j]); 
        }
    }
    cout << fixed << setprecision(10) << dyn[N] + T << '\n'; 
    return 0;
}