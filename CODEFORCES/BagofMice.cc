#include "bits/stdc++.h"

using namespace std;

const int maxf = 1002;

double dyn[maxf][maxf][2];
int n, m;

double f(int w, int b, int turn)
{
    if (b < 0 || w < 0) return 0;
    if (w + b == 0) return turn;
    if (dyn[w][b][turn] != -1.0) return dyn[w][b][turn];
    double &ret = dyn[w][b][turn];
    ret = 1.0 * w / (w + b);
    if (turn && w + b > 1) {
        ret += 1.0 * b * (b - 1) / ((w + b) * (w + b - 1)) * (1.0 - f(w, b - 2, turn ^ 1));
        ret += 1.0 * b * w / ((w + b) * (w + b - 1)) * (1.0 - f(w - 1, b - 1, turn ^ 1));
    }
    else {
        ret += 1.0 * b / (w + b) * (1.0 - f(w, b - 1, turn ^ 1));
    }
    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < maxf; i++)
    for (int j = 0; j < maxf; j++) {
        dyn[i][j][0] = dyn[i][j][1] = -1.0;
    }
    cout << fixed << setprecision(10) << f(n, m, 0) << '\n';
    return 0;
}