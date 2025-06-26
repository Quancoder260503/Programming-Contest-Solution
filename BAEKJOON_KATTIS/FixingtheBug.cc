#include "bits/stdc++.h"

using namespace std;

int N, T; 
double f; 
vector<double>Prob, Severity;
vector<int>Attempt;  
vector<vector<vector<double>>>dyn;  

double memo(int mask, int time, int fattempt) { 
    if(time == 0 || mask == (1 << N) - 1) return 0;   
    double &ret = dyn[mask][time][fattempt]; 
    if(ret > -1.0) return ret; 
    ret = 0; 
    pair<double, int>opt; 
    for(int i = 0; i < N; i++) { 
        if(mask & (1 << i)) continue;
        opt = max({opt, {Prob[i] * Severity[i], i}}); 
    }
    int bug = opt.second; 
    double oBug = Prob[bug]; 
    Prob[bug] *= f; 
    Attempt[bug]++; 
    ret += (1.0 - oBug) * memo(mask, time - 1, fattempt + 1);
    Attempt[bug]--; 
    Prob[bug] = oBug; 
    ret += oBug * (Severity[bug] +  memo(mask | (1 << bug), time - 1, fattempt - Attempt[bug]));    
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    cin >> N >> T >> f; 
    Prob.resize(N); 
    Severity.resize(N);   
    Attempt.resize(N); 
    for(int i = 0; i < N; i++) { 
        cin >> Prob[i] >> Severity[i]; 
    }
    dyn.resize((1 << N), vector<vector<double>>(T + 1, vector<double>(T + 1, -1.0)));
    cout << fixed << setprecision(15) << memo(0, T, 0) << '\n'; 
    return 0; 
}