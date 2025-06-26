#include "bits/stdc++.h"
using namespace std;
const int MAX = 305;
int SG[MAX][MAX]; 
int main(void)
{
    for (int i = 0; i < MAX; i++) for (int j = 0; j < MAX; j++)
    {
        if(abs(i - j) <= 1) SG[i][j] = -1;
        else 
        {
            set<int>S;
            for(int k = 0; k < i; k++) S.insert(SG[k][j]); 
            for(int k = 0; k < j; k++) S.insert(SG[i][k]);
            while(S.count(SG[i][j])) SG[i][j]++; 
        }
    }
    int N;
    cin >> N;
    auto get_win = [&](int xa, int xb, int ya, int yb)
    {
        return (abs(xa - ya) + abs(xb - yb) > 1 && (SG[xa][ya] != SG[xb][yb] || SG[xa][ya] == -1 || SG[xb][yb] == -1)); 
    }; 
    while(N--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a, --b, --c, --d; 
        int ret = 0; 
        for (int i = a - 1; i >= 0 && (i != c || b != d); i--) ret += (get_win(i, b, c, d) == 0);
        for (int i = b - 1; i >= 0 && (a != c || i != d); i--) ret += (get_win(a, i, c, d) == 0);
        for (int i = c - 1; i >= 0 && (i != a || b != d); i--) ret += (get_win(a, b, i, d) == 0);
        for (int i = d - 1; i >= 0 && (a != c || i != b); i--) ret += (get_win(a, b, c, i) == 0);
        cout << ret << '\n'; 
    }
    return 0;
}