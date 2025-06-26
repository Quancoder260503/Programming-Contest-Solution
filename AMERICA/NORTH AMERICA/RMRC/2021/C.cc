#include "bits/stdc++.h"
using namespace std;
int main()
{
    int n, k;

    cin >> n >> k;

    vector<int> seated(k);
    for (int i = 0; i < k; ++i)
    {
        cin >> seated[i];
    }

    int total = 0;

    for (int i = 1; i < k; ++i)
    {
        total += (seated[i] - seated[i-1] - 2) / 2;

    }

    total += (n + seated[0] - seated[k-1] -2) / 2;
    cout << total << endl;
    return 0;
}