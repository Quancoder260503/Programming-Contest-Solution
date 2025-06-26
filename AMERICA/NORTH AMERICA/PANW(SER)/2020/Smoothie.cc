#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int K, R;
    while (cin >> K >> R)
    {
        vector<int> arr(K);
        for (int i = 0; i < K; i++)
            cin >> arr[i];
        int64_t ret = 0;
        for (int i = 0; i < R; i++)
        {
            int amt = 1e8;
            for (int j = 0; j < K; j++)
            {
                int x;
                cin >> x;
                if (x == 0) continue; 
                amt = min(amt, arr[j] / x);
            }
            int price;
            cin >> price;
            ret = max(ret, (int64_t)price * amt);
        }
        cout << ret << '\n';
    }
    return 0;
}