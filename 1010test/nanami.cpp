#include <stdio.h>
char s[1005][1005];
int sc, wc, oc, xc; //starter counter, wall counter
int main()
{
    freopen("nanami.in", "r", stdin);
    freopen("nanami.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("\n%s", s[i] + 1);
    for (int i = 2; i < n; ++i)
        for (int j = 2; j < m; ++j)
            if (s[i][j] == 's')
                ++sc;
            else if (s[i][j] == '#')
                ++wc;
            else if (s[i][j] == 'o')
                ++oc;
            else if (s[i][j] == 'X')
                ++xc;
    if (!wc && sc == 1 && !xc)
        return 0 * printf("%d", oc);
    return 0;
}
