#include "bits/stdc++.h"
using namespace std;
#define Lint long long
const int M = 30; 
class DiceOperation
{
public:
    double solve(vector<int> dice)
    {
        int N = dice.size(); 
        vector<vector<int>>bit(N, vector<int>(M));
        vector<vector<int>>T(N, vector<int>(M)); 
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                int cur_dice = (1 << (j + 1));
                bit[i][j] = ((dice[i] + 1) / cur_dice) * (1 << j);
                if(dice[i] & (1 << j))
                {
                    bit[i][j] += (dice[i] + 1) % (1 << j); 
                }
            }
        }  
        double ret = 0;
        for(int at = 0; at < M; at++)
        {
            for (int mask = 0; mask < (1 << N); mask++)
            {
                if(__builtin_popcount(mask) & 1)
                {
                    double prob = 1;
                    for (int i = 0; i < N; i++)
                    {
                        if (mask & (1 << i))
                        {
                            prob = prob * (double)(bit[i][at]);
                        }
                        else
                        {
                            prob = prob * (double)(dice[i] - bit[i][at]);
                        }
                        prob = prob / (double) dice[i]; 
                    }
                    ret += (double)(1 << at) * prob;
                }
            }
        }
        cout << fixed << setprecision(15) << ret << '\n'; 
        return ret; 
        // the probability of rolling dice so that the corresponding xorsum has bit ith on. 
    };
};
signed main(void)
{
    DiceOperation test; 
    test.solve({5, 9, 6}); 
    return 0; 
}