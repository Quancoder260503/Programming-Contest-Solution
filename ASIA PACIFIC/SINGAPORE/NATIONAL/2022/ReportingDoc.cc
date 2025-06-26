#include "bits/stdc++.h"

using namespace std;

const int SQRT = 380 ;
const int maxf = 2e5 + 10;

int dyn[SQRT][SQRT]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    string s;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < SQRT; j++) {
            dyn[j][i % j] += (s[i] == '0' ? 1 : 0);
        }
    }
    cin >> m;
    for (int tc = 0; tc < m; tc++) {
        int t;
        cin >> t; 
        if(t < 3) {
            int at;
            cin >> at;
            --at; 
            s[at] = (s[at] == '1' ? '0' : '1');
            for (int j = 1; j < SQRT; j++) {
                dyn[j][at % j] += (t == 1 ? -1 : 1);
            }
        }
        else {
            int x, k;
            cin >> x >> k;
            --x; 
            if (k < SQRT) {
                cout << dyn[k][x] << '\n';
            } else {
                int ret = 0; 
                for (int i = x; i < n; i += k) {
                    ret += (s[i] == '0' ? 1 : 0);
                }
                cout << ret << '\n';
            }
        }
    } 
    return 0;
}