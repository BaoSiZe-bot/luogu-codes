#include <cstring>
#include <stdio.h>
char s[205][205];
struct Edge
{
    int v, p;
} e[80005];
int ed[320005], ecnt;
inline void add(int u, int v)
{
    e[++ecnt] = {v, ed[u]};
    ed[u] = ecnt;
}
int md[80005], vs[80005], n, cnt;
int dx[] = {-1, -2, 1, 2, -1, -2, 1, 2};
#include <cstring>
#include <stdio.h>
char s[205][205];
struct Edge
{
    int v, p;
} e[80005];
int ed[320005], ecnt;
inline void add(int u, int v)
{
    e[++ecnt] = {v, ed[u]};
    ed[u] = ecnt;
}
int md[80005], vs[80005], n, cnt;
int dx[] = {-1, -2, 1, 2, -1, -2, 1, 2};
int dy[] = {-2, -1, -2, -1, 2, 1, 2, 1};
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
inline int cvt(int x, int y)  // convert (x, y) to id
{
    return (x - 1) * n + y;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%200s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            if (s[i][j] ^ '0')
                continue;
            ++cnt;
            for (int id = 0; id < 8; ++id)
            {
                int u = i + dx[id], v = j + dy[id];
                if (s[u][v] ^ '0')
                    continue;
                if (u >= 1 && u <= n && v >= 1 && v <= n && !((i + j) & 1))
                    add(cvt(i, j), cvt(u, v) + n * n);
            }
        }
    int res = 0;
    for (int i = 1; i <= n * n; ++i)
    {
        memset(vs, 0, sizeof(vs));
        res += Hungarian(i);
    }
    printf("%d", cnt - res);
    return 0;
}
int dy[] = {-2, -1, -2, -1, 2, 1, 2, 1};
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
inline int cvt(int x, int y)  // convert (x, y) to id
{
    return (x - 1) * n + y;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%200s", s[i] + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            if (s[i][j] ^ '0')
                continue;
            ++cnt;
            for (int id = 0; id < 8; ++id)
            {
                int u = i + dx[id], v = j + dy[id];
                if (s[u][v] ^ '0')
                    continue;
                if (u >= 1 && u <= n && v >= 1 && v <= n && !((i + j) & 1))
                    add(cvt(i, j), cvt(u, v) + n * n);
            }
        }
    int res = 0;
    for (int i = 1; i <= n * n; ++i)
    {
        memset(vs, 0, sizeof(vs));
        res += Hungarian(i);
    }
    printf("%d", cnt - res);
    return 0;
}
