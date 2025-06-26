#include "bits/stdc++.h"
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >> n;

    cout << fixed << setprecision(10) << 100.0 / (double) n << endl;
    cout << fixed << setprecision(10) << 100.0 / (100.0 - n) << endl;

    return 0;
}