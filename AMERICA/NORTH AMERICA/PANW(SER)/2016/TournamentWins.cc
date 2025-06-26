#include "bits/stdc++.h"

using namespace std;

#define double long double 

double Comb(int n, int k) { 
    double ret = 0;
    for(int i = 0; i < k; i++) { 
        ret += log(n - i) - log(i + 1); 
    } 
    return ret; 
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0);  
    cout.tie(0);
    int log, r; 
    cin >> log >> r;
    double ret = 0;
    for(int num_win = 1; num_win <= log; num_win++) { 
        int choose = (1 << num_win) - 1; 
        if(choose + r > (1 << log) || choose + 1 > (1 << log)) break; 
        double curr = exp(Comb((1 << log) - r, choose) - Comb((1 << log) - 1, choose));
        ret += curr; 
    }
    cout << fixed << setprecision(5) << ret << '\n'; 
    return 0; 
}