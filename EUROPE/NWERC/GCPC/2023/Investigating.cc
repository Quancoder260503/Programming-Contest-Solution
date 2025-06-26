#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 500000;

int main(void)
{
    map<int, int>str;
    set<int> emp;
    for (int i = 1; i < maxf; i++) emp.insert(i);
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        str[i] = x;
        if (emp.count(x)) emp.erase(x);
    }
    cin >> q;
    for (int i = 0, pos; i < q; i++)
    {
        cin >> pos;
        pos--; 
        int at = str[pos]; 
        int to = *emp.lower_bound(at);
        cout << to << '\n'; 
        emp.erase(to);
        emp.insert(at);
        str[pos] = to; 
    }
    return 0;
}