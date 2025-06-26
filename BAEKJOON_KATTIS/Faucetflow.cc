#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int32_t left, right;
    while (cin >> left >> right)
    {
        if (left == 0 && right == 0) break;
        vector<int32_t> flow;
        for (int i = left; i <= right; i += 2)
        {
            int32_t x;
            cin >> x;
            flow.push_back(x);
        }
        int32_t lefth, righth;
        lefth = righth = 0;
        for (int i = left, j = 0; i < 0; i += 2, j++)
        {
            lefth = max(lefth, flow[j]);
        }
        for (int i = right, j = flow.size() - 1; i > 0; i -= 2, j--)
        {
            righth = max(righth, flow[j]);
        }
        if (lefth > righth)
        {
            reverse(flow.begin(), flow.end());
            swap(lefth, righth);
            swap(left,  right);
            left  = -left; 
            right = -right;
        }
        int leftt = lefth = 0;
        for (int i = left, j = 0; i < 0; i += 2, j++)
        {
            lefth = max(lefth, flow[j]);
            leftt += 2 * lefth;
        }
        int32_t midL, midR, midt;
        midL = midR = 0;
        for (int i = left; i < 0; i += 2, midR++);
        midL = midR - 1;
        midt = 2 * lefth;
        leftt -= 2 * lefth;
        while (flow[midL] < lefth)
        {
            midL--;
            midt += 2 * lefth;
            leftt -= 2 * lefth;
        }
        while (flow[midR] < lefth)
        {
            midR++;
            midt += 2 * lefth;
        }
        if (lefth == righth)
        {
            int rightt;
            rightt = righth = 0;
            for (int i = right, j = flow.size() - 1; i > 0; i -= 2, j--)
            {
                righth = max(righth, flow[j]);
                rightt += 2 * righth; 
            }
            cout << 2 * min(rightt, leftt) + midt << '\n'; 
        }
        else
        {
            int rightt = 0;
            for (int j = midR; flow[j] <= lefth; j++)
            {
                rightt += 2 * lefth;
            }
            cout << leftt + midt + min(leftt, rightt) << '\n'; 
        }
    }
    return 0;
}