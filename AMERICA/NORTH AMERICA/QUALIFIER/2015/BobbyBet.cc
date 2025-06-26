#include "bits/stdc++.h"

using namespace std; 

#define double long double
#define COMB_MAXA 5000
#define COMB_MAXB 5000

const double eps = 1e-6; 

double Comb[COMB_MAXA + 1][COMB_MAXB + 1]; 

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    int tc, r, s, x, y, w; 
    cin >> tc; 
    Comb[0][0] = 1; 
    for(int i = 1; i < COMB_MAXA; i++) 
    for(int j = 0; j <= i; j++) { 
        Comb[i][j] = Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0); 
    }
    while(tc--) { 
        cin >> r >> s >> x >> y >> w; 
        double ret = 0; 
        double Prob = 1.0 - 1.0 * (r - 1) / s; 
        for(int i = x; i <= y; i++) { 
            ret += Comb[y][i] * pow(1 - Prob, y - i) * pow(Prob, i); 
        }  
        ret = ret * w;
        cout << (ret > 1 + eps ? "yes" : "no") << '\n'; 
    }
    return 0; 
}