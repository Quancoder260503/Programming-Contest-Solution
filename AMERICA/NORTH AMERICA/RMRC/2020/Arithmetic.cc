#include "bits/stdc++.h"
using namespace std;
#define double long double 
#define EPS 1e-12
int cmp(double a, double b)
{
    return fabs(a - b) < EPS; 
}
int main(void)
{
    int N;
    double pA;  
    string P; 
    while(cin >> N >> pA >> P)
    {
        pA = pA / 8.0; 
        double p = 0; 
        double coef = 0.5;
        for(int i = 2; i < P.length(); i++)
        {
            p += (P[i] - '0') * coef;
            coef = coef * 0.5; 
        }
        for(int mask = 0; mask < (1 << N); mask++) 
        {
            double a, b;
            a = 0.0; b = 1.0; 
            for(int i = 0; i < N; i++)
            {
                ((mask >> i) & 1 ? a : b) = a + (b - a) * pA; 
            }
            if(cmp(a, p))
            {
                for(int i = 0; i < N; i++) cout << ((mask >> i) & 1 ? 'B' : 'A'); 
                cout << '\n'; 
                goto done;
            }
        }
    done:;  
    }
    return 0;
}