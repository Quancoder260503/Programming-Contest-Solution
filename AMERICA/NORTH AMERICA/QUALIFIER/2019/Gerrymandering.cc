#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int N, M;
    cin >> N >> M;
    vector<int>a(M), b(M); 
    double tot = 0; 
    for(int i = 0; i < N; i++)
    {
        int d, av, bv;
        cin >> d >> av >> bv;
        tot += av + bv;
        a[--d] += av;
        b[d]   += bv; 
    }
    double suma = 0, sumb = 0; 
    for(int i = 0; i < M; i++) {
        int sum = (a[i] + b[i]) / 2 + 1;
        if(a[i] > b[i])
        {
            cout << 'A' << " " << a[i] - sum << " " << b[i] << '\n'; 
            sumb += b[i];
            suma += a[i] - sum; 
        }
        else 
        {
            cout << 'B' << " " << a[i] << " " << b[i] - sum << '\n'; 
            suma += a[i];
            sumb += b[i] - sum; 
        }
    }
    cout << fixed << setprecision(10) << 1.0 * abs(suma - sumb) / tot << '\n';  
    return 0; 
}