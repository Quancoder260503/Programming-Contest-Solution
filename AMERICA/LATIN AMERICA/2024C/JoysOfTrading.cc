#include "bits/stdc++.h"

using namespace std; 

const double eps = 1e-6;

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cout << fixed << setprecision(10); 
    cin >> n;
    vector<int>a(n), b(n), w(n), u(n); 
    for(int i = 0; i < n; i++) { 
        cin >> a[i] >> u[i] >> b[i] >> w[i]; 
    }
    int64_t sa = 0, sb = 0; 
    for(int i = 0; i < n; i++) { 
        sa += a[i] * u[i]; 
        sb += b[i] * w[i]; 
    }
    int64_t sa2 = 0, sb2 = 0; 
    for(int i = 0; i < n; i++) { 
        sb2 += b[i] * (w[i] + u[i]); 
    }
    vector<int>ord(n);
    iota(ord.begin(), ord.end(), 0); 
    sort(ord.begin(), ord.end(), [&](int x, int y) { 
        return 1LL * a[x] * b[y] < 1LL * a[y] * b[x]; 
    });
    double ret = sa + sb;  
    for(auto i : ord) { 
        if(sa2 <= sa && sb2 <= sb) ret = min(ret, double(sa2 + sb2));
        double xa = double(sa - sa2) / a[i], xb = double(sb2 - sb) / b[i]; 
        for(auto x : {xa, xb}) { 
            double ya = sa2 + a[i] * x, yb = sb2 - b[i] * x; 
            if(eps < x && x + eps < u[i] + w[i] && ya < sa + eps && yb < sb + eps) { 
                ret = min(ret, ya + yb); 
            }
        }
        sb2 = sb2 - b[i] * (w[i] + u[i]); 
        sa2 = sa2 + a[i] * (w[i] + u[i]); 
        if(sa2 <= sa && sb2 <= sb) ret = min(ret, double(sa2 + sb2)); 
    }
    cout << ret << '\n'; 
    return 0; 
}