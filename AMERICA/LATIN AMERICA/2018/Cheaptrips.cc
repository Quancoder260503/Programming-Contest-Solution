#include "bits/stdc++.h"

using namespace std; 

const int maxf = 2e5 + 10;
const double INF = 1e9;  

int C[maxf], D[maxf], N; 
double dyn[maxf]; 

double solve(int i)
{
    if(i > N) return 0;
    if(dyn[i] != INF) return dyn[i]; 
    double &ret = dyn[i]; 
    ret = C[i] + solve(i + 1); 
    int acc = D[i]; 
    double sum = C[i]; 
    for(int j = 1; j < 6; j++)
    {
        if(i + j > N || acc >= 120) break; 
        ret = min(ret, sum + (j == 1 ? 0.5 : 0.25) * C[i + j] + solve(i + j + 1));
        acc += D[i + j]; 
        sum += (j == 1 ? 0.5 : 0.25) * C[i + j]; 
    }
    return ret; 
}

int main(void)
{
    cin >> N; 
    for(int i = 0; i < maxf; i++) dyn[i] = INF; 
    for(int i = 1; i <= N; i++) cin >> D[i] >> C[i]; 
    cout << fixed << setprecision(2) << solve(1) << '\n';  
    return 0; 
}