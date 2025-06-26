#include "bits/stdc++.h"

using namespace std; 


double Comb(int a, int b) { 
    #define COMB_MAXA 5000
    #define COMB_MAXB 5000
    static double combmemo[COMB_MAXA + 1][COMB_MAXB + 1]; 
    if(a < b || b < 0) return 0; 
    if(!a) return 1;
    double &ret = combmemo[a][b]; 
    if(ret < 1) ret = Comb(a - 1, b - 1) + Comb(a - 1, b); 
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    string S; 
    int N; 
    while(cin >> S) {
        if(S == "[END]") { break; }
        cin >> N;
        double ret = N * (Comb(5 * N - 5, 1) * Comb(5, 4) + 1 + Comb(5 * N - 5, 2) * Comb(5, 3)) / Comb(5 * N, 5); 
        cout << fixed << setprecision(10) << ret << '\n'; 
    }
    return 0; 
}