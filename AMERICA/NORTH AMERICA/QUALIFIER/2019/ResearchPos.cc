#include "bits/stdc++.h"

using namespace std; 

const int maxf = 1000;  

double dyn[maxf][maxf], p[maxf]; 

int main(void)
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> p[i]; 
    double ret = 0;  
    sort(p + 1, p + n + 1); 
    reverse(p + 1, p + n + 1); 
    dyn[0][0] = 1;
    for(int i = 1; i <= n; i++)
    {
        double prob = 0; 
        for(int j = 0; j <= i; j++)
        {
            dyn[i][j] = (j > 0 ? p[i] / 100.0 * dyn[i - 1][j - 1] : 0) + (1.0 - p[i] / 100.0) * dyn[i - 1][j]; 
            prob += dyn[i][j] * (j == 0 ? 0 : pow(j, 1.0 * j / i)); 
        }
        ret = max(ret, prob); 
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}