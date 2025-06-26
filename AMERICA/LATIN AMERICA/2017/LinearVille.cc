#include "bits/stdc++.h"

using namespace std;

const int INF = 1e9; 

int main(void) { 
    int n, q; 
    cin >> n; 
    vector<int>accx(n), accy(n), rx(n), ry(n), xprefix(n), xsuffix(n), yprefix(n), ysuffix(n);
    for(int i = 0; i < n - 1; i++) cin >> rx[i]; 
    for(int i = 0; i < n - 1; i++) cin >> ry[i]; 
    for(int i = 1; i < n; i++) {
        accx[i] = accx[i - 1] + rx[i - 1]; 
        accy[i] = accy[i - 1] + ry[i - 1]; 
    }
    int32_t alt = -INF; 
    for(int i = 0; i < n; i++) { 
        if(i && rx[i - 1] == 1) alt = i; 
        xprefix[i] = alt; 
    }
    alt = INF; 
    for(int i = 0; i < n; i++) { 
        if(i && ry[i - 1] == 1) alt = i; 
        yprefix[i] = alt; 
    }
    alt = INF; 
    for(int i = n - 1; i >= 0; i--) { 
        if(rx[i] == 1) alt = i; 
        xsuffix[i] = alt; 
    }
    alt = INF; 
    for(int i = n - 1; i >= 0; i--) { 
        if(ry[i] == 1) alt = i; 
        ysuffix[i] = alt; 
    }
    cin >> q;
    for(int i = 0; i < q; i++) { 
        int xa, ya, xb, yb; 
        cin >> xa >> ya >> xb >> yb; 
        --xa, --xb, --ya, --yb; 
        if(xa > xb) swap(xa, xb); 
        if(ya > yb) swap(ya, yb); 
        int cc = accx[xb] - accx[xa] + accy[yb] - accy[ya]; 
        int ret = INF; 
        if(yb - ya > xb - xa) { 
            int m = (yb - ya) - (xb - xa); 
            m = (m & 1 ? m - 1 : m); 
            int dist = xa - xprefix[xa]; 
            if(dist * 2 <= m) { 
                ret = min(ret, 8 * dist + m); 
            }
            dist = xsuffix[xb] - xb;
            if(dist * 2 <= m) { 
                ret = min(ret, 8 * dist + m);
            }
            ret = min(ret, 5 * m);
            if(xsuffix[xa] < xb) { 
                ret = min(ret, m); 
            } 
        }
        else {
            int m = (xb - xa) - (yb - ya);
            m = (m & 1 ? m - 1 : m);
            int dist = ya - yprefix[ya];
            if (dist * 2 <= m)
            {
                ret = min(ret, 8 * dist + m);
            }
            dist = ysuffix[yb] - yb;
            if (dist * 2 <= m)
            {
                ret = min(ret, 8 * dist + m);
            }
            ret = min(ret, 5 * m);
            if (ysuffix[ya] < yb)
            {
                ret = min(ret, m);
            }
        }
        ret += cc;
        cout << ret << '\n'; 
    }
    return 0; 
}