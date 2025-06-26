#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m; 
    cin >> n >> m;
    set<int> ms; 
    for (int i = 0; i < m; i++) {
        char c;
        int a, b; 
        cin >> c >> a;
        if (c == '-') ms.insert(a), ms.insert(a + n);
        else if (c == '+') ms.erase(a),   ms.erase(a + n);
        else {
            cin >> b;
            if(ms.count(a) || ms.count(b)) {
                cout << "impossible\n";
                continue; 
            }
            if(ms.empty()) {
                cout << "possible\n";
                continue; 
            }
            if (a > b) swap(a, b); 
            auto itl = ms.lower_bound(a);
            auto itr = ms.lower_bound(b); 
            if(itr != ms.begin()) {
                itr--;
                if(*itl > *itr) {
                    cout << "possible\n";
                    goto done; 
                }
            }
            else {
                cout << "possible\n"; 
                goto done;
            }
            itl = ms.lower_bound(b);
            itr = ms.lower_bound(a + n);
            if (itr != ms.begin()) {
                itr--;
                if (*itl > *itr) {
                    cout << "possible\n";
                    goto done; 
                }
            }
            else {
                cout << "possible\n";
                goto done; 
            }
            cout << "impossible\n";
        done:;
        }
    }
    return 0;
}