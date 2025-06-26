#include "bits/stdc++.h"

using namespace std;

const int maxf = 1000;
const int maxh = 12; 

int d, n, c, a[maxf], b[maxf];
double dyn[maxf][maxh][maxh][maxh], C[maxf][maxf]; 

double f(int r, int i, int j, int k) { 
    if(r == maxf) return 0.0; 
    if((i == 0) && (j == 0 || k == 0)) return r; 
    if(dyn[r][i][j][k] != -1) return dyn[r][i][j][k]; 
    double &ret = dyn[r][i][j][k]; 
    ret = 0; 
    for(int ni = 0; ni <= i; ni++) 
    for(int nj = 0; nj <= j; nj++) 
    for(int nk = 0; nk <= k; nk++) if ((n + ni + nj + nk >= i + j + k + d) && (ni + nj + nk <= d)) { 
        ret += f(r + 1, i - ni, j - nj, k - nk) * C[i][ni] * C[j][nj] * C[k][nk] * C[n - i - j - k][d - ni - nj - nk] / C[n][d];
    }
    return ret; 
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    C[0][0] = 1; 
    for(int i = 1; i < maxf; i++) for(int j = 0; j <= i; j++) {
        C[i][j] = C[i - 1][j] + (j ? C[i - 1][j - 1] : 0);  
    } 
    cin >> n >> d >> c;
    for(int i = 0; i < c; i++) { 
        cin >> a[i];  
    }
    for(int i = 0; i < c; i++) { 
        cin >> b[i]; 
    }
    int sa = 0, sb = 0, sc = 0; 
    for(int i = 0; i < c; i++) {
        for(int j = 0; j < c; j++) if(a[i] == b[j]) {
            sc++;  
        }   
        int flag = true;      
        for(int j = 0; j < c; j++) { 
            flag &= (a[i] != b[j]); 
        }
        if(flag) sa++; 
        flag = true;      
        for(int j = 0; j < c; j++) { 
            flag &= (b[i] != a[j]); 
        }
        if(flag) sb++; 
    }
    for(int i = 0; i < maxf; i++) 
    for(int j = 0; j < maxh; j++)
    for(int k = 0; k < maxh; k++)
    for(int t = 0; t < maxh; t++) { 
        dyn[i][j][k][t] = -1.0; 
    }
    cout << fixed << setprecision(10) << f(0, sc, sa, sb) << '\n'; 
    return 0;  
}