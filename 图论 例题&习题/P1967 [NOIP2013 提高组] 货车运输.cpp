#include <algorithm>
#include <cstring>
#include <cstdio>
#include <set>
struct Edge
{
    int u, v, w;
    bool operator<(const Edge &other) const
    {
        return w > other.w;
    }
} e[100005];
int p[10005], res[100005];
std::set<int> qry[50005];
inline int fd(int x)
{
    return ~p[x] ? p[x] = fd(p[x]) : x;
}
int main()
{
    memset(p, 0xff, sizeof p);
    memset(res, 0xff, sizeof res);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    std::sort(e + 1, e + m + 1);
    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        qry[x].insert(i);
        qry[y].insert(i);
    }
    for (int i = 1; i <= m; ++i)
    {
        int u = fd(e[i].u), v = fd(e[i].v);
        if (u != v)
        {
            if (qry[u].size() < qry[v].size())
                u ^= v ^= u ^= v;
            for (int j : qry[v])
            {
                if (qry[u].count(j))
                {
                    res[j] = e[i].w;
                    qry[u].erase(j);
                }
                else
                    qry[u].insert(j);
            }
            p[v] = u;
        }
    }
    for (int i = 1; i <= q; ++i)
        printf("%d\n", res[i]);
    return 0;
}
