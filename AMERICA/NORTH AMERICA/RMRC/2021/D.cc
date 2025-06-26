#include <iostream>
#include <unordered_map>
#include "bits/stdc++.h"
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> display(n);
    vector<int> current(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> display[i];
    }

    for (int i = 0; i < n; ++i)
    {
        cin >> current[i];
    }

    long long h1c = 0;
    long long h2c = 0;
    unordered_map<int, long long> h1;
    unordered_map<int, long long> h2;

    for (int i = 0; i < n; ++i)
    {
        if (i != 0 && h1c == 0 && h2c == 0)
        {
            cout << "# ";
        }

        int item = display[i];
        if (h2[item] == 0)
        {
            if (h1[item] == 0)
                h1c += 1;

            h1[item] += 1;
        }
        else
        {
            if (h2[item] == 1)
            {
                h2c -= 1;
            }
            {
                h2[item] -= 1;
            }
        }

        item = current[i];
        if (h1[item] == 0)
        {
            if (h2[item] == 0)
                h2c += 1;

            h2[item] += 1;
        }
        else
        {
            if (h1[item] == 1)
            {
                h1c -= 1;
                
            }
            
            {
                h1[item] -= 1;
            }
        }

        cout << item << " ";
    }
    return 0;
}