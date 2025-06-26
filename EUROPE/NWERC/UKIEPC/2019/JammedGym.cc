#include "bits/stdc++.h"

using namespace std; 

const double INF = 1e20; 
const double PI  = acos(-1); 

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n;
    vector<int>a(n);
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    }
    cin >> m;
    vector<int>b(n + 1);
    for(int i = 0; i < m; i++) { 
        cin >> b[i]; 
    }
    b[m] = m;  
    vector<vector<double>>d(m + 1, vector<double>(m + 1));
     for(int i = 0; i < m; i++) { 
        d[m][i] = d[i][m] = 1; 
    }
    auto calc = [&](int i, int j) -> double { 
        return 2 * sin(min(j - i, m - j + i) * PI / m); 
    }; 
    for(int i = 0; i < m; i++) { 
        for(int j = i + 1; j < m; j++) { 
            d[i][j] = d[j][i] = calc(i, j); 
        }
    } 
    vector<vector<double>>dyn(n + 1, vector<double>(m + 1, -1)); 
    function<double(int, int)> f = [&](int i, int j) -> double { 
        if(i >= n) return 0; 
        if(dyn[i][j] > 0) return dyn[i][j];
        double &ret = dyn[i][j];
        ret = INF; 
        for(int k = 0; k < m; k++) if(b[k] == a[i]) { 
            ret = min(ret, d[j][k] + f(i + 1, k)); 
        }
        return ret;     
    };    
    cout << fixed << setprecision(10) << f(0, m) << '\n';    
    return 0; 
}