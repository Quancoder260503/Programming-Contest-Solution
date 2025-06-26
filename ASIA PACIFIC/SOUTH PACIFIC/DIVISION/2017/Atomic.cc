#include "bits/stdc++.h"
using namespace std;
signed main(void)
{
    int N;
    while (cin >> N)
    {
        vector<string> S(N);
        vector<double> arr(N);
        for (int i = 0; i < N; i++)
            cin >> S[i] >> arr[i];
        string P;
        cin >> P;
        int M = P.length();
        double ret = 0;
        for (int i = 0; i < M; i++)
        {
            bool temp = 0;
            if (i + 1 < M && isdigit(P[i + 1]) == 0)
            {
                string moc = P.substr(i, 2);
                int j, k;
                for (j = 0; j < N; j++)
                {
                    if (moc == S[j])
                    {
                        int coef = 0;
                        k = i + 2;
                        while (k < M && isdigit(P[k]))
                        {
                            coef = coef * 10 + (P[k] - '0');
                            k++;
                        }
                        ret += (coef == 0 ? 1 : coef) * arr[j];
                        i = k - 1;
                        temp = 1;
                        break; 
                    }
                }
            }
            if(!temp)
            {
                string moc = P.substr(i, 1);
                int j, k;
                for (j = 0; j < N; j++)
                {
                    if (moc == S[j])
                    {
                        int coef = 0;
                        k = i + 1;
                        while (k < M && isdigit(P[k]))
                        {
                            coef = coef * 10 + (P[k] - '0');
                            k++;
                        }
                        ret += (coef == 0 ? 1 : coef) * arr[j];
                        i = k - 1;
                        break; 
                    }
                }
            }
        }
        cout << fixed << setprecision(10) << ret << '\n';
    }
    return 0;
}