#include "bits/stdc++.h"

using namespace std; 

const int maxf = 3005; 

double dyn[maxf][maxf]; 

int n, k; 

double func(int i, int j) { 
    if(i == 0 && j == 0) return 0.0; 
    double &ret = dyn[i][j]; 
    if(ret + 1 > 0) return ret; 
    ret = 1.0 + (i ? i * func(i - 1, j + 1) : 0) + (j ? j * func(i, j - 1) : 0);  
    double prob = i + j; 
    ret = ret / prob;
    return ret; 
}

map<pair<int, int>, double>cache; 

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    int tc; 
    cin >> tc; 
    cout << fixed << setprecision(10); 
    for(int i = 0; i < maxf; i++) 
    for(int j = 0; j < maxf; j++) {
        dyn[i][j] = -1.0; 
    }
    while(tc--) { 
        cin >> n >> k;
        vector<int>a(n);
        for(int i = 0, x; i < k; i++) { 
            cin >> x; 
            a[--x]++; 
        } 
        int ctra = 0, ctrb = 0;
        for(int i = 0; i < n; i++) { 
            ctra += (a[i] == 0); 
            ctrb += (a[i] == 1); 
        } 
        double ret = func(ctra, ctrb); 
        cout << ret * n << '\n';
    }
    return 0; 
}


/*
   dyn[i][j][k] = {expected number of addtional rounds to reach state(i, j, k) where there are i values with 0 occurences, 
   j values with 1 occureneces and k values with atleast 2 occurences}
   ret = dyn[0][0][n]
   However note that in every states i + j + k == n
   --> reduce the state to (i, j)
*/