#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int opt = 0;
    vector<int> ret(1e4 + 10);
    for (int i = 0; i < 5; i++) {
        string c; 
        for (int j = 1; j < 27; j++)
            if (j & (1 << i)) {
                c += char('a' + j - 1);
            }
        cout << "? " << c << endl;
        int x;
        cin >> x;
        for (int j = 0, y; j < x; j++) {
            cin >> y;
            opt = max(opt, y);
            --y;
            ret[y] |= (1 << i);
        }
    }
    cout << "! ";
    for (int i = 0; i < opt; i++) {
        cout << char(ret[i] + 'a' - 1);
    }
    cout << endl;
    return 0;
}