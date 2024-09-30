#include <string.h>
#include <stdio.h>
int md[205], vs[205], n, m, t;
bool mp[205][205];
inline bool Hungarian(int x)
{
    for (int i = 1; i <= m; ++i)
        if (!mp[x][i] && !vs[i])
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
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 1; i <= t; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        mp[x][y] = 1;
    }
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        memset(vs, 0, sizeof vs);
        res += Hungarian(i);
    }
    printf("%d", res);
    return 0;
}
