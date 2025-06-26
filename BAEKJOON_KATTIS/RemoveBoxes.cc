#include "bits/stdc++.h"

using namespace std; 

class Solution
{
public:
    int removeBoxes(vector<int> &boxes)
    {
        static int dyn[102][102][102];
        memset(dyn, -1, sizeof(dyn));
        vector<pair<int, int>> arr;
        arr.push_back({boxes[0], 1});
        for (int i = 1; i < boxes.size(); i++)
        {
            if (arr.back().first == boxes[i])
            {
                arr.back().second++;
            }
            else
            {
                arr.push_back({boxes[i], 1});
            }
        }
        function<int(int, int, int)> f = [&](int l, int r, int len)
        {
            if (l >= r)
                return (arr[l].second + len) * (arr[l].second + len);
            if (dyn[l][r][len] != -1)
                return dyn[l][r][len];
            int &ret = dyn[l][r][len];
            ret = 0;
            ret = max(ret, f(l, r - 1, 0) + (arr[r].second + len) * (arr[r].second + len));
            for (int k = l; k < r; k++)
                if (arr[k].first == arr[r].first)
                {
                    ret = max(ret, f(l, k, len + arr[r].second) + f(k + 1, r - 1, 0));
                }
            return ret;
        };
        return f(0, arr.size() - 1, 0);
    }
};