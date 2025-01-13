#include <cstdio>
#include <cstring>
int mp[105][105], md[105], vs[105], n, m, k;
inline bool Hungarian(int x)
{
    for (int i = 1; i <= m; ++i)
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
    while (scanf("%d", &n), n)
    {
        scanf("%d%d", &m, &k);
        memset(mp, 0, sizeof mp);
        for (int i = 1; i <= k; ++i)
        {
            int rub, a, b;
            scanf("%d%d%d", &rub, &a, &b);
            mp[a][b] = 1;
        }
        int res = 0;
        memset(md, 0, sizeof md);
        for (int i = 1; i <= n; ++i)
        {
            memset(vs, 0, sizeof vs);
            res += Hungarian(i);
        }
        printf("%d\n", res);
    }
    return 0;
}
