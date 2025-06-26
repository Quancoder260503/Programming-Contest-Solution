#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 10;

int ctr[maxf];
bitset<maxf> dyn;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << "N\n";
        return 0;
    }
    vector<int> g(n), c(n);
    int sum = 0, zero = false;
    for (int i = 0; i < n; i++)
    {
        cin >> g[i] >> c[i];
        ctr[g[i]]++;
        sum += g[i];
        if(!g[i]) zero = true; 
    }
    int gc = c[0];
    for (int i = 1; i < n; i++) {
        gc = gcd(gc, c[i]);
    }
    dyn[0] = 1;
    for (int i = 0; i < maxf; i++)
    {
        for (int j = 1; j <= ctr[i]; j = j << 1) {
            dyn |= (dyn << (j * i));
            ctr[i] = ctr[i] - j;
        }
        if (ctr[i] > 0) dyn |= (dyn << (ctr[i] * i));
    }
    int b = sum + zero; 
    for (int i = 1; i < b; i++) if (dyn[i] && abs(sum - 2 * i) % gc == 0) {
        cout << "Y\n";
        return 0;
    }
    cout << "N\n";
    return 0;
}