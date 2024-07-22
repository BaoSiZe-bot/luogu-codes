//same as P1967
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <set>
#define int long long
struct Edge
{
    int u, v, w;
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
} e[1000005];
int p[1000005], res[1000005];
std::set<int> qry[1000005];
inline int fd(int x)
{
    return ~p[x] ? fd(p[x]) : x;
}
signed main()
{
    int n, m;
    bool flg = false;
    while (~scanf("%lld%lld", &n, &m))
    {
        if (flg)
            puts("\n");
        flg = 1;
        memset(p, 0xff, sizeof p);
        for (int i = 1; i <= m; ++i)
            qry[i].clear();
        for (int i = 1; i <= m; ++i)
            scanf("%lld%lld%lld", &e[i].u, &e[i].v, &e[i].w);
        std::sort(e + 1, e + m + 1);
        int q;
        scanf("%lld", &q);
        for (int i = 1; i <= q; ++i)
        {
            int x, y;
            scanf("%lld%lld", &x, &y);
            qry[x].insert(i);
            qry[y].insert(i);
            res[i] = -1;
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
        for (int i = 1; i < q; ++i)
            printf("%lld\n", res[i]);
        printf("%lld", res[q]);
    }
    return 0;
}
