#include <algorithm>
#include <stdio.h>
#include <string.h>
struct Edge
{
    int u, v;
    double w;
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
} e[200005];
int p[100005], h[100005], x[100005], y[100005], res, m;  //FIXED: added memset(p, 0xff, sizeof p);
inline double diss(int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
inline int fd(int x)  // find parent
{
    return ~p[x] ? p[x] = fd(p[x]) : x;
}
inline bool mg(int id)  // merge u, v
{
    int u = fd(e[id].u), v = fd(e[id].v);
    if (u ^ v)
    {
        res = e[id].w;
        if (h[u] <= h[v])
            p[u] = v;
        else
            p[v] = u;
        if (h[u] == h[v])
            ++h[u];
        return true;
    }
    return false;
}
#include <math.h>
int main()
{
    memset(p, 0xff, sizeof p);
    int s, p;
    scanf("%d%d", &s, &p);
    for (int i = 1; i <= p; ++i)
    {
        scanf("%d%d", x + i, y + i);
        for (int j = 1; j < i; ++j)
            e[++m] = {i, j, diss(x[i], y[i], x[j], y[j])};
    }
    std::sort(e + 1, e + m + 1);
    int md = 0; //别误会是Merged
    for (int i = 1; i <= m; ++i)
    {
        md += mg(i);
        if (md >= p - s)
            return 0 * printf("%.2lf", sqrt(res));
    }
    return 0;
}
