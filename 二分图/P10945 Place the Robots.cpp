#include <cstdio>
#include <cstring>
char s[55][55];
struct Edge
{
    int v, p;
} e[2005];
int ed[1005], cnt, tst;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
int pos[55][55], pov[55][55];
int md[2505], vs[2505], n;
inline bool Hungarian(int x)
{
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (vs[to] != tst)
        {
            vs[to] = tst;
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
    int t;
    scanf("%d", &t);
    for (int $ = 1; $ <= t; ++$)
    {
        memset(pos, 0, sizeof pos);
        memset(ed, 0, sizeof ed);
        memset(md, 0, sizeof md);
        cnt = 0;
        int a, b;
        scanf("%d%d", &a, &b);
        for (int i = 1; i <= a; ++i)
            scanf("\n%s", s[i] + 1);
        int tot = 0;
        for (int i = 1; i <= a; ++i)
            for (int j = 1; j <= b; ++j)
                if (s[i][j] != '#')
                {
                    (j == 1 || s[i][j - 1] == '#') && (++tot);
                    pos[i][j] = tot;
                }
        int tmp = tot;
        for (int j = 1; j <= b; ++j)
            for (int i = 1; i <= a; ++i)
                if (s[i][j] != '#')
                {
                    (i == 1 || s[i - 1][j] == '#') && (++tot);
                    pov[i][j] = tot;
                }
        for (int i = 1; i <= a; ++i)
            for (int j = 1; j <= b; ++j)
                if (s[i][j] == 'o')
                    add(pos[i][j], pov[i][j]);
        int res = 0;
        for (int i = 1; i <= tmp; ++i)
        {
            tst = i;
            res += Hungarian(i);
        }
        printf("Case :%d\n%d\n", $, res);
    }
    return 0;
}
