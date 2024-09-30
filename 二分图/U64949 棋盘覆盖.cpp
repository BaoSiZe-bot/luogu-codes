#include <cstring>
#include <stdio.h>
using ll = long long;
int md[100005], vs[100005], n, m;
bool mp[205][205];
int d[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
int cr(int a, int b)
{
    return (a - 1) * n + b;
}
struct Edge
{
    int v, p;
} e[200005];
int ed[100005], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline bool Hungarian(int x)
{
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (!vs[to])
        {
            vs[to] = 1;
            if (!md[to] || Hungarian(md[to]))
            {
                md[to] = x;
                return 1;
            }
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
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (!mp[i][j])
                for (int p = 0; p < 4; ++p)
                {
                    int k = i + d[p][0], l = j + d[p][1];
                    if (k >= 1 && l >= 1 && k <= n && l <= n && !mp[k][l])
                        add(cr(i, j), cr(k, l));
                }
    int res = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if ((i + j) & 1)
            {
                memset(vs, 0, sizeof vs);
                res += Hungarian(cr(i, j));
            }
    return 0 * printf("%d\n", res);
}
