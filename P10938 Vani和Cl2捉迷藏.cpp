#include <cstring>
#include <stdio.h>
int mp[205][205], md[205], vs[205], n, m;
inline bool Hungarian(int x)
{
    for (int i = 1; i <= n; ++i)
        if (mp[x][i] && !vs[i])
        {
            vs[i] = 1;
            if (!md[i] || Hungarian(md[i]))
            {
                md[i] = x;
                return 1;
            }
        }
    return 0;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        mp[x][y] = 1;
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                mp[i][j] |= mp[i][k] && mp[k][j];
    int res = n;
    for (int i = 1; i <= n; ++i)
    {
        memset(vs, 0, sizeof vs);
        res -= Hungarian(i);
    }
    printf("%d\n", res);
    return 0;
}
/*
4 4
1 2
3 2
3 4
4 2
 */
