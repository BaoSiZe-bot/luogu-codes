#include <string.h>
#include <stdio.h>

bool dp[200005];
int a[7];
int main()
{
    while (scanf("%d%d%d%d%d%d", a + 1, a + 2, a + 3, a + 4, a + 5, a + 6))
    {
        int s = a[1] + 2 * a[2] + 3 * a[3] + 4 * a[4] + 5 * a[5] + 6 * a[6], ms = s >> 1;
        if (s == 0)
            break;
        if (s & 1)
        {
            printf("Can't\n");
            continue;
        }
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        for (int j = 1; j <= 6; ++j)
        {
            int t = a[j], p = 1;
            while (t >= p)
            {
                for (int i = ms; i >= j * p; --i)
                    dp[i] |= dp[i - j * p];
                t -= p;
                p <<= 1;
            }
            if (t > 0)
                for (int i = ms; i >= j * t; --i)
                    dp[i] |= dp[i - j * t];
        }
        printf("Can");
        if (!dp[ms])
            printf("'t");
        printf("\n");
    }
    return 0;
}
