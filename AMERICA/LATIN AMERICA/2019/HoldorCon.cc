#include "bits/stdc++.h"

using namespace std;
#define double long double 

const int maxf = 350; 
const int win = 75; 

double dyn[maxf][maxf][maxf]; 

double Phold(int i, int j, int k)
{
    return 1.0 - dyn[j][i + k][0]; 
}

double Pcont(int i, int j, int k)
{
    double ret = 0; 
    for(int dice = 1; dice <= 6; dice++)
    {
        if(dice == 1 || dice + k + i > win)
        {
            ret += 1 - dyn[j][i][0]; 
        }
        else 
        {
            ret += dyn[i][j][k + dice];  
        }
    }
    return ret / 6; 
}

int main(void)
{
    int Q; 
    while(cin >> Q)
    {
        int ctr = 0; 
        for(;;)
        {
            for (int i = 0; i < win; i++) for (int j = 0; j < win; j++) for (int k = win - i; k >= 0; k--)
            {
                dyn[i][j][k] = max(Pcont(i, j, k), Phold(i, j, k));
            }
            ctr++;
            if(ctr == 30) break; 
        }
        for(int i = 0; i < Q; i++)
        {
            int A, B, C;
            cin >> A >> B >> C; 
            cout << (Pcont(A, B, C) > Phold(A, B, C) ? 'C' : 'H') << '\n'; 
           // cout << Pcont(A, B, C) << " " << Phold(A, B, C) << '\n'; 
        }
    }
    return 0; 
}

// dyn[Alice total score][Alice Turn Score][Bob total score ]