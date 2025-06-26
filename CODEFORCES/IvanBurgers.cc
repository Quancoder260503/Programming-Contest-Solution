#include "bits/stdc++.h"

using namespace std;

const int maxb = 20;
const int maxf = 5e5 + 2;

int a[maxf][maxb + 1], p[maxf][maxb]; 

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m; 
    cin >> n;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        for(int b = maxb; b >= 0; b--) { 
            a[i][b] = a[i - 1][b]; 
            p[i][b] = p[i - 1][b]; 
        }
        int c = i; 
        for(int b = maxb; b >= 0; b--) if(x & (1LL << b)) { 
            if(!a[i][b]) {
                a[i][b] = x;
                p[i][b] = c;
                break;
            }
            if(c > p[i][b]) {
                swap(p[i][b], c);
                swap(a[i][b], x); 
            }
            x = x ^ a[i][b]; 
        }
    }
    cin >> m;
    for (int _ = 0, l, r; _ < m; _++)
    {
        cin >> l >> r;
        int64_t ret = 0;
        for(int b = maxb; b >= 0; b--) if(((ret ^ a[r][b]) > ret) && (p[r][b] >= l)) { 
            ret = ret ^ a[r][b]; 
        } 
        cout << ret << '\n'; 
    }
    return 0;
}