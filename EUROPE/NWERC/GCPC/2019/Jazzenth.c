#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    int N, C;
    while (scanf("%d%d", &N, &C) == 2)
    {
        int res = 0;
        for (int i = 0; i < N; i++)
        {
            int m, s;
            scanf("%d:%d", &m, &s);
            res += m * 60 + s;
        }
        res = res - (N - 1) * C; 
        int h = res / 3600;
        int m = (res - h * 3600) / 60;
        int s = (res - m * 60 - h * 3600);
        if (h < 10)
            printf("0%d:",h);
        else
            printf("%d:", h);
        if (m < 10)
            printf("0%d:", m);
        else
            printf("%d:", m);
        if (s < 10)
            printf("0%d\n", s);
        else
            printf("%d\n", s);
    }
    return 0;
}