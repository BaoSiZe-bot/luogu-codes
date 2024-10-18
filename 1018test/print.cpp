#include <stdio.h>
char s[1005][1005];
int res[1005], tot;
int main()
{
    freopen("print.in", "r", stdin);
    freopen("print.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%1000s", s[i] + 1);
    if (n == 1)
    {
        for (int i = 1; i <= m; ++i)
        {
            if (m % i)
                continue;
            bool f = 1;
            for (int j = i + 1; j <= m; ++j)
                if (s[1][j % i] ^ s[1][i])
                {
                    f = 0;
                    break;
                }
            if (f)
                res[++tot] = i;
        }
        printf("%d\n", tot);
        for (int i = 1; i <= tot; ++i)
            printf("%d\n", res[i]);
    }
    return 0;
}
