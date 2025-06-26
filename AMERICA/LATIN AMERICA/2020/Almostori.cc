#include "bits/stdc++.h"
using namespace std;
const int MAX = 100;
vector<int> den{1};
map<int, vector<int>> mp;
vector<int> curr;
void doit(int ctr = 1)
{
    if (ctr == 10)
        return;
    int big = den.back();
    for (int i = 0; i < ctr; i++)
        for (int j = i; j < ctr; j++)
        {
            int sden = den[i] + den[j];
            if (sden <= big || sden > MAX)
                continue;
            curr.push_back(den[i]);
            curr.push_back(den[j]);
            if (!mp.count(sden) || mp[sden].size() > curr.size())
            {
                mp[sden] = curr;
            }
            den.push_back(sden);
            doit(ctr + 1);
            den.pop_back();
            curr.pop_back();
            curr.pop_back();
        }
    return;
}
int main(void)
{
    clock_t tStart = clock();
    doit();
    int n, d;
    while (cin >> n >> d)
    {
        if (n > 1)
            cout << "*" << '\n';
        else
        {
            auto ret = mp[d];
            for (int i = 0; i < ret.size(); i++)
            {
                cout << 1 << " " << ret[i] << '\n';
            }
        }
    }
    // printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    return 0;
}